#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


struct ShaderProgramSource {
	std::string VertexSource;
	std::string FragmentSource;
};

static ShaderProgramSource parseShader(const std::string &filepath) {
	std::ifstream stream(filepath);

	enum class ShaderType { NONE = -1, VERTEX = 0, FRAGMENT = 1 };

	std::string line;
	std::stringstream ss[2];  // two for the two shader types
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line)) {
		if (line.find("#shader") != std::string::npos) {
			if (line.find("vertex") != std::string::npos) {
				type = ShaderType::VERTEX;
			} else if (line.find("fragment") != std::string::npos) {
				type = ShaderType::FRAGMENT;
			}
		} else {
			ss[int(type)] << line << '\n';
		}
	}

	return {ss[0].str(), ss[1].str()};
}

static unsigned int compileShader(unsigned int type,
				  const std::string &source) {
	unsigned int id = glCreateShader(type);
	const char *src = source.c_str();
	GLCall(glShaderSource(id, 1, &src, nullptr));
	GLCall(glCompileShader(id));

	int result;
	GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

	if (result == GL_FALSE) {
		int length;
		GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
		char *message = (char *)alloca(length * sizeof(char));
		GLCall(glGetShaderInfoLog(id, length, &length, message));
		std::cout << "Failed to compile "
			  << (type == GL_VERTEX_SHADER ? "vertex" : "fragment")
			  << " shader!" << std::endl;
		std::cout << message << std::endl;
		GLCall(glDeleteShader(id));
		return 0;
	}

	return id;
}

static unsigned int createShader(const std::string &vertexShader,
				 const std::string &fragmentShader) {
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	GLCall(glAttachShader(program, vs));
	GLCall(glAttachShader(program, fs));
	GLCall(glLinkProgram(program));
	GLCall(glValidateProgram(program));

	GLCall(glDeleteShader(vs));
	GLCall(glDeleteShader(fs));

	return program;
}

int main() {
	GLFWwindow *window;

	if (!glfwInit()) return -1;

	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window) {
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) return -1;

	float positions[] = {
	    -0.5f, -0.5f,  // 0
	    0.5f,  -0.5f,  // 1
	    0.5f,  0.5f,   // 2
	    -0.5f, 0.5f	   // 3
	};

	unsigned int indices[] = {0, 1, 2, 2, 3, 0};


	unsigned int vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));


	VertexBuffer vb(positions, 4 * 2 * sizeof(float));

	GLCall(glEnableVertexAttribArray(0));
	GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
				     2 * sizeof(float), 0));

	IndexBuffer ib(indices, 6);


	ShaderProgramSource source = parseShader("res/shaders/Triangle.shader");
	unsigned int shader =
	createShader(source.VertexSource, source.FragmentSource);
	GLCall(glUseProgram(shader));

	GLCall(int location = glGetUniformLocation(shader, "u_color"));
	Assert(location != -1);
	GLCall(glUniform4f(location, 1.0f, 0.0f, 0.0f, 1.0f));

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	glfwSwapInterval(1);

	// unbind everything
	GLCall(glBindVertexArray(0));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

	float r = 0.0f;
	float increment = 0.05f;
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT);

		GLCall(glUseProgram(shader));
		GLCall(glUniform4f(location, r, 0.0f, 0.0f, 1.0f));

		GLCall(glBindVertexArray(vao));
		ib.Bind();

		GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
		if (r > 1.0f) {
			increment = -0.01f;
		} else if (r < 0.0f) {
			increment = 0.01f;
		}
		r += increment;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	GLCall(glDeleteProgram(shader));
	glfwTerminate();
	return 0;
}

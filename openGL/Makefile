# libs for GLFW and GLEW
LIBS := -lGL -lGLU -lglfw -lGLEW
CXX := clang++ -g
CXXFLAGS := -O3

all: openglapp

Renderer.o: src/Renderer.cpp
	$(CXX) $(CXXFLAGS) -c src/Renderer.cpp

VertexBuffer.o: src/VertexBuffer.cpp
	$(CXX) $(CXXFLAGS) -c src/VertexBuffer.cpp

IndexBuffer.o: src/IndexBuffer.cpp
	$(CXX) $(CXXFLAGS) -c src/IndexBuffer.cpp

main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp

openglapp: Renderer.o VertexBuffer.o IndexBuffer.o main.o
	$(CXX) $(CXXFLAGS) -o openglapp Renderer.o VertexBuffer.o IndexBuffer.o main.o $(LIBS)

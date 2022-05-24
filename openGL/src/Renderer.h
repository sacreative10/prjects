#pragma once

#include <GL/glew.h>

#define Assert(x) \
	if (!(x)) asm("int3")
#define GLCall(x)       \
	GLClearError(); \
	x;              \
	Assert(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char *function, const char *file, int line);

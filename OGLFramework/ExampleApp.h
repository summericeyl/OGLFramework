#ifndef __EXAMPLE_APPLICATION_H__
#define __EXAMPLE_APPLICATION_H__

#include "BasicApplication.h"
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>

using namespace oglplus;

class ExampleApp : public BasicApp
{
public:
	ExampleApp();
	void Reshape(GLuint width, GLuint height);
	void Render(double);

private:
	// wrapper around the current OpenGL context
	Context gl;

	// Vertex shader
	VertexShader vs;

	// Fragment shader
	FragmentShader fs;

	// Program
	Program prog;

	// A vertex array object for the rendered triangle
	VertexArray triangle;

	// VBOs for the triangle's vertices and colors
	Buffer verts;
	Buffer colors;
};

#endif
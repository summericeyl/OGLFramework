
#include "ExampleApp.h"

ExampleApp::ExampleApp()
{
	try
	{
		// Set the vertex shader source
		std::string vs_string = read_from_file("../media/glsl/glsl.vs");
		vs.Source(vs_string.c_str());
		// compile it
		vs.Compile();
	}
	catch (CompileError&)
	{
// 		// Set the fallback vertex shader source
// 		vs.Source(" \
// 				#version 120\n \
// 				attribute vec3 Position; \
// 				attribute vec3 Color; \
// 				varying vec4 vertColor; \
// 				void main(void) \
// 				{ \
// 					gl_Position = vec4(Position, 1.0); \
// 					vertColor = vec4(Color, 1.0); \
// 				} \
// 			");
// 		// compile it
// 		vs.Compile();
	}

	try
	{
		std::string fs_string = read_from_file("../media/glsl/glsl.fs");
		fs.Source(fs_string.c_str());
		fs.Compile();
	}
	catch (CompileError&)
	{
// 		fs.Source(" \
// 				#version 120\n \
// 				varying vec4 vertColor; \
// 				void main(void) \
// 				{ \
// 					gl_FragColor = vertColor; \
// 				} \
// 			");
// 		fs.Compile();
	}

	// attach the shaders to the program
	prog.AttachShader(vs);
	prog.AttachShader(fs);
	// link and use it
	prog.Link();
	prog.Use();

	// bind the VAO for the triangle
	triangle.Bind();

	GLfloat triangle_verts[9] = {
		0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f
	};
	// bind the VBO for the triangle vertices
	verts.Bind(Buffer::Target::Array);
	// upload the data
	Buffer::Data(Buffer::Target::Array, 9, triangle_verts);
	// setup the vertex attribs array for the vertices
	VertexArrayAttrib(prog, "Position").Setup<GLfloat>(3).Enable();
	//

	GLfloat triangle_colors[9] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};
	// bind the VBO for the triangle colors
	colors.Bind(Buffer::Target::Array);
	// upload the data
	Buffer::Data(Buffer::Target::Array, 9, triangle_colors);
	// setup the vertex attribs array
	VertexArrayAttrib(prog, "Color").Setup<GLfloat>(3).Enable();
	// VertexArrayAttrib(prog, "Color").Setup<GLfloat>(3).Disable();

	gl.ClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	gl.Disable(Capability::DepthTest);
}

void ExampleApp::Reshape(GLuint width, GLuint height)
{
	gl.Viewport(width, height);
}

void ExampleApp::Render(double)
{
	gl.Clear().ColorBuffer();

	gl.DrawArrays(PrimitiveType::Triangles, 0, 3); 
}

std::unique_ptr<BasicApp> makeExample()
{
	return std::unique_ptr<BasicApp>(new ExampleApp);
}
#include <iostream>
#include "ExampleApp.h"

#ifdef  _DEBUG
#pragma comment(lib, "oglplusd.lib")
#else
#pragma comment(lib, "oglplus.lib")
#endif //  _DEBUG
#pragma comment(lib, "glew32.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "opengl32.lib")


class GLFWInitializer
{
public:
	GLFWInitializer(void)
	{
		if (!glfwInit())
		{
			throw std::runtime_error("GLFW initialization error");
		}

		// TODO: this caused problems for some users
		// have a look what GLFW actually does here
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, OGLPLUS_GL_VERSION_MAJOR);
		//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, OGLPLUS_GL_VERSION_MINOR);
	}

	~GLFWInitializer(void)
	{
		glfwTerminate();
	}
};


class GLAPIInitializer
{
public:
	GLAPIInitializer(
		int /*gl_ver_major*/ = 3,
		int /*gl_ver_minor*/ = 3
	)
	{
		glewExperimental = GL_TRUE;
		GLenum init_result = glewInit();
		glGetError();
		if (init_result != GLEW_OK)
		{
			throw std::runtime_error(
				"OpenGL/GLEW initialization error."
			);
		}
	}
};

void run_loop(
	std::unique_ptr<BasicApp>& app,
	GLFWwindow* window,
	GLuint width,
	GLuint height
)
{
	GLuint mouse_x = width / 2;
	GLuint mouse_y = height / 2;
	// os::steady_clock os_clock;
	// ExampleClock clock;
	while (true)
	{
		//clock.Update(os_clock.seconds());
		//if (!example->Continue(clock)) break;
		app->Render(0.0);

		glfwSwapBuffers(window);
		glfwPollEvents();

		int new_x, new_y;
		double tmp_x, tmp_y;
		glfwGetWindowSize(window, &new_x, &new_y);
		if ((int(width) != new_x) || (int(height) != new_y))
		{
			if (new_x <= 0) new_x = 1;
			if (new_y <= 0) new_y = 1;
			width = GLuint(new_x);
			height = GLuint(new_y);
			app->Reshape(width, height);
		}

		glfwGetCursorPos(window, &tmp_x, &tmp_y);
		new_x = std::floor(tmp_x);
		new_y = std::floor(tmp_y);
		if ((int(mouse_x) != new_x) || (int(mouse_y) != new_y))
		{
			if (new_x <= 0) new_x = 1;
			if (new_y <= 0) new_y = 1;
			mouse_x = GLuint(new_x);
			mouse_y = GLuint(new_y);
			app->MouseMove(
				mouse_x,
				height -
				mouse_y,
				width,
				height
			);
		}

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, 1);
			break;
		}
		if (glfwWindowShouldClose(window))
		{
			break;
		}
	}
}

void run_app(
	const char* screenshot_path,
	int argc,
	char** argv
)
{
	GLFWInitializer glfw_initializer;
	const GLuint width = 800, height = 600;
	GLFWwindow* window = glfwCreateWindow(
		width,
		height,
		"OGLplus example",
		NULL,
		NULL
	);
	if (!window)
	{
		throw std::runtime_error("Error creating GLFW3 window");
	}
	else
	{
		glfwMakeContextCurrent(window);
		GLAPIInitializer api_init;

		std::unique_ptr<BasicApp> app(makeExample());
		app->Reshape(width, height);
		app->MouseMove(width / 2, height / 2, width, height);

		run_loop(app, window, width, height);
	}
}

int main(int argc, char** argv)
{
	run_app(0, argc, argv);
	return 0;
}
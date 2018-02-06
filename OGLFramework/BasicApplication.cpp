#include <iostream>
#include "BasicApplication.h"
#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <fstream>

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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	}

	~GLFWInitializer(void)
	{
		glfwTerminate();
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

void run_app(const char* window_title, int argc, char** argv)
{
	GLFWInitializer glfw_initializer;
	const GLuint width = 800, height = 600;
	GLFWwindow* window = 0;
	if (window_title == 0)
		window = glfwCreateWindow(width, height,
			"OpenGL Application", NULL, NULL);
	else
		window = glfwCreateWindow(width, height,
			window_title, NULL, NULL);
	if (!window)
	{
		throw std::runtime_error("Error creating GLFW3 window");
	}
	else
	{
		glfwMakeContextCurrent(window);
		oglplus::GLAPIInitializer api_init;

		std::unique_ptr<BasicApp> app(makeExample());
		app->Reshape(width, height);
		app->MouseMove(width / 2, height / 2, width, height);

		run_loop(app, window, width, height);
	}
}

std::string read_from_file(const std::string filename)
{
	std::ifstream ifs(filename);
	if (ifs.is_open())
	{
		std::string content((std::istreambuf_iterator<char>(ifs)),
			(std::istreambuf_iterator<char>()));
		return content;
	}
	else
	{
		return std::string();
	}
}
#ifndef __BASIC_APPLICTION_H__
#define __BASIC_APPLICTION_H__

#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <memory>
#include <string>

class BasicApp
{
public:
	virtual ~BasicApp(void)
	{ }


	/// Reshape event handler
	virtual void Reshape(GLuint width, GLuint height) = 0;

	/// Mouse move event handler
	virtual void MouseMoveNormalized(float x, float y, float aspect)
	{
		(void)(x + y + aspect);
	}

	/// Mouse move event handler
	virtual void MouseMove(GLuint x, GLuint y, GLuint width, GLuint height)
	{
		return MouseMoveNormalized(
			(float(x) - width * 0.5f) / (width * 0.5f),
			(float(y) - height* 0.5f) / (height* 0.5f),
			float(width) / height
		);
	}

	/// Rendering procedure with simple timing
	virtual void Render(double /*time*/)
	{

	}

	/// The time of the default screenshot
	virtual double ScreenshotTime(void) const
	{
		return 1.0; // [s]
	}

	/// Single frame time in the screenshot capture sequence
	virtual double FrameTime(void) const
	{
		return 1.0 / 25.0;
	}

	/// The number of heat-up sequence frames
	virtual GLuint HeatUpFrames(void) const
	{
		return 5;
	}

	/// The screenshot capture heat-up sequence start time
	virtual double HeatUpTime(void) const
	{
		return ScreenshotTime() - HeatUpFrames()*FrameTime();
	}
};


std::unique_ptr<BasicApp> makeExample();
void run_app(const char* window_title, int argc, char** argv);
std::string read_from_file(const std::string filename);

#endif
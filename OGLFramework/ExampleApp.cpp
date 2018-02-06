
#include "ExampleApp.h"

void ExampleApp::Reshape(GLuint width, GLuint height)
{

}

std::unique_ptr<BasicApp> makeExample()
{
	return std::unique_ptr<BasicApp>(new ExampleApp);
}
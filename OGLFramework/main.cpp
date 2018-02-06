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

int main(int argc, char** argv)
{
	run_app(0, argc, argv);
	return 0;
}
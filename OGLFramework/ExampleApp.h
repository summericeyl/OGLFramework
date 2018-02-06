#ifndef __EXAMPLE_APPLICATION_H__
#define __EXAMPLE_APPLICATION_H__

#include "BasicApplication.h"

class ExampleApp : public BasicApp
{
public:
	void Reshape(GLuint width, GLuint height);
};

#endif
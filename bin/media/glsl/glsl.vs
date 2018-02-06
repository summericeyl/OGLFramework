#version 330
in vec3 Position; 
in vec3 Color; 
out vec4 vertColor; 
void main(void) 
{
	gl_Position = vec4(Position, 1.0); 
	vertColor = vec4(Color, 1.0); 
} 

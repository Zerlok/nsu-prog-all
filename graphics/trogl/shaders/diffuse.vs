#version 120

attribute vec4 position;
attribute vec4 normal;
attribute vec4 color;

//out vec3 vectorNormal;


void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * position;
	gl_FrontColor = color;
}

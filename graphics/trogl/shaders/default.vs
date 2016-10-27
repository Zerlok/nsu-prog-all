#version 120

attribute vec4 position;
attribute vec4 color;


void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * position;
	gl_FrontColor = color;
}

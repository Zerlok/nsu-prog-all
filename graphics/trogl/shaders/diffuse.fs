#version 120

in vertexNormal;

attribute vec4 position;
attribute vec4 color;

uniform vec4 lampPosition;


void main()
{
	gl_FragColor = color;
}

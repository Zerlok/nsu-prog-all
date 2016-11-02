#version 120

attribute vec4 position;
attribute vec4 normal;
attribute vec4 color;


varying vec4 vertexPosition;
varying vec4 vertexNormal;
varying vec4 vertexColor;


void main()
{
	gl_Position = gl_ModelViewProjectionMatrix * position;
	vertexPosition = position;
	vertexNormal = normal;
	vertexColor = color;
}

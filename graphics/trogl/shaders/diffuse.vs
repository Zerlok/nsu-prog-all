#version 120

attribute vec4 position;
attribute vec4 normal;

varying vec4 vertexPosition;
varying vec3 vertexNormal;


void main()
{
	vertexPosition = gl_ModelViewMatrix * position;
	vertexNormal = (gl_ModelViewMatrix * normal).xyz;

	gl_Position = gl_ModelViewProjectionMatrix * position;
}

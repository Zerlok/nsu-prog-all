#version 130


attribute vec4 position;
attribute vec4 normal;
attribute vec2 uvMap;

varying vec4 vertexPosition;
varying vec3 vertexNormal;
varying vec2 vertexUV;


void main()
{
	vertexPosition = gl_ModelViewMatrix * position;
	vertexNormal = (gl_ModelViewMatrix * normal).xyz;
	vertexUV = uvMap;

	gl_Position = gl_ModelViewProjectionMatrix * position;
}

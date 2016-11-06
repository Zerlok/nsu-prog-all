#version 120

attribute vec4 position;
attribute vec4 normal;
attribute vec4 color;

uniform vec4 meshPosition;

varying vec4 vertexPosition;
varying vec3 vertexNormal;
varying vec4 vertexColor;


void main()
{
        gl_Position = gl_ModelViewProjectionMatrix * (position + meshPosition);

        vertexPosition = gl_ModelViewMatrix * position;
	vertexNormal = normalize(gl_ModelViewMatrix * normal).xyz;
	vertexColor = color;
}

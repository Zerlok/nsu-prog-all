#version 120

attribute vec4 position;
attribute vec4 normal;
attribute vec4 color;

uniform vec3 meshPosition;
uniform float cosSqAlpha;


void main()
{
	vec3 pos = position.xyz;
	pos -= meshPosition;
	float k = 1 / sqrt(dot(pos, pos));
	pos = pos * cosSqAlpha + pos * k * (1 - cosSqAlpha);
	pos += meshPosition;

	gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);
	gl_FrontColor = color;
}

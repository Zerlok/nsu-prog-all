#version 120

attribute vec4 position;
attribute vec4 color;

uniform vec4 trogl_objPosition;
uniform float cosSqAlpha;


void main()
{
	vec3 pos = position.xyz;
	pos -= trogl_objPosition.xyz;
	float k = 1 / sqrt(dot(pos, pos));
	pos = pos * cosSqAlpha + pos * k * (1 - cosSqAlpha);
	pos += trogl_objPosition.xyz;
	gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);
	gl_FrontColor = color;
}

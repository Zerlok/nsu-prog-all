#version 120


uniform int lampType;
uniform vec4 lampPosition;
uniform float lampPower;
uniform vec4 lampDirection;
uniform vec4 lampColor;
uniform float lampIA;
uniform float lampOA;


varying vec4 vertexPosition;
varying vec4 vertexNormal;
varying vec4 vertexColor;


void main()
{
	// TODO: count deffuse.
	// TODO: count specular.
	// TODO: count ambient.
	vec4 color;
	vec4 direction = lampPosition - vertexPosition;
	float distance = length(direction);
	color = lampColor * lampPower * dot(direction, vertexNormal) / pow(distance, 2);
	// color = direction;

	gl_FragColor = color;
}

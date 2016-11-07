#version 120


uniform vec4 meshPosition;

uniform int lampType;
uniform vec4 lampPosition;
uniform float lampPower;
uniform vec4 lampDirection;
uniform vec4 lampColor;
uniform float lampIA;
uniform float lampOA;


varying vec4 vertexPosition;
varying vec3 vertexNormal;
varying vec4 vertexColor;


void main()
{
	// TODO: count deffuse.
	// TODO: count specular.
	// TODO: count ambient.

	vec3 direction = lampPosition.xyz - vertexPosition.xyz;
	float distance = length(direction);
	direction = normalize(direction);

	vec4 color;
	color = lampColor * max(dot(vertexNormal, direction), 0.0);
	// color = color * lampPower / pow(distance, 2);

	gl_FragColor = clamp(color, 0.0, 1.0);
}

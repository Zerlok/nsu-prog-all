#version 330


struct LampStruct
{
    int type;
	vec4 position;
	float power;
	vec4 direction;
	vec4 color;
	float ia;
	float oa;
};

const int LIGHTTEXTLIM = 16;


in vec4 vertexPosition;
in vec4 vertexNormal;

uniform LampStruct lamp;

uniform sampler2D samples[LIGHTTEXTLIM];
uniform int texturesLen;


out vec4 color;
out float depth;


void main()
{
    color = clamp(dot(vertexNormal, vec4(0.0, 0.0, 1.0, 0.0)), 0.0, 1.0) * lamp.power * lamp.color;
	depth = gl_FragCoord.z;
}

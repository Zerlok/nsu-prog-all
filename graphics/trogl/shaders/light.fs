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

uniform mat4 MV;

uniform LampStruct lamp;

uniform sampler2D samples[LIGHTTEXTLIM];
uniform int texturesLen;


out vec4 color;


void main()
{
    float ndcDepth = (2.0 * gl_FragCoord.z - gl_DepthRange.near - gl_DepthRange.far) / (gl_DepthRange.far - gl_DepthRange.near);
	float clipDepth = ndcDepth / gl_FragCoord.w;
	color = vec4((clipDepth * 0.5) + 0.5);
}

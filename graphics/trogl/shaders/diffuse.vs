#version 330


in vec4 position;
in vec4 normal;
in vec2 uvMap;

uniform mat4 MV;
uniform mat4 MVP;

out vec4 vertexPosition;
out vec3 vertexNormal;
out vec2 vertexUV;


void main()
{
    vertexPosition = MV * position;
	vertexNormal = (MV * normal).xyz;
	vertexUV = uvMap;

    gl_Position = MVP * position;
}

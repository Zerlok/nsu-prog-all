#version 330


in vec4 position;
in vec4 normal;
in vec2 uvMap;

uniform mat4 MW;
uniform mat4 MV;
uniform mat4 MP;

out vec4 vertexPosition;
out vec3 vertexNormal;
out vec2 vertexUV;


void main()
{
    vertexPosition = MV * MW * position;
	vertexNormal = (MV * MW * normal).xyz;
	vertexUV = uvMap;

    gl_Position = MP * MV * MW * position;
}

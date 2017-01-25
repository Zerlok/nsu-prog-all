#version 330


in vec4 position;
in vec4 normal;
in vec2 uvMap;

uniform mat4 MW;
uniform mat4 MV;
uniform mat4 MP;

out vec4 vertexPosition;
out vec4 vertexNormal;


void main()
{
    vertexPosition = MP * MV * MW * position;
	vertexNormal = MV * MW * normal;
	gl_Position = vertexPosition;
}

#version 330


in vec4 position;
in vec4 normal;
in vec2 uvMap;

uniform mat4 MW;
uniform mat4 MV;

out vec4 vertexPosition;


void main()
{
    vertexPosition = MV * MW * position;
	gl_Position = vertexPosition;
}

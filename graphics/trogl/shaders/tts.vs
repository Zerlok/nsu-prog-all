#version 330


in vec4 position;
in vec4 normal;
in vec2 uvMap;

uniform mat4 MV;
uniform mat4 MP;

out vec2 vertexUV;


void main()
{
    gl_Position = MP * MV * position;
	vertexUV = uvMap;
}

#version 330


in vec4 position;
in vec4 normal;
in vec2 uvMap;

out vec2 vertexUV;


void main()
{
    gl_Position = position;
	vertexUV = uvMap;
}

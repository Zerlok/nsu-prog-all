#version 330


in vec2 vertexUV;
uniform sampler2D text;

out vec4 color;


void main()
{
    color = vec4(texture2D(text, vertexUV).xyz, 1.0f);
}

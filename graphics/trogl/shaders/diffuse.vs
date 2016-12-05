#version 130


struct TextureStruct
{
	float binded;
	vec2 map;
	float colorMix;
	sampler2D data;
};


attribute vec4 position;
attribute vec4 normal;
attribute vec2 uvMap;

varying vec4 vertexColor;
varying float vertexColorMix;
varying vec4 vertexPosition;
varying vec3 vertexNormal;

uniform TextureStruct text;


void main()
{
	vertexColor = mix(vec4(1.0f, 1.0f, 1.0, 1.0f), texture(text.data, uvMap + text.map), text.binded);
	//vertexColor = mix(vec4(1.0f, 1.0f, 1.0, 1.0f), vec4(uvMap, 0.5f, 1.0f), text.binded);
	vertexColorMix = text.colorMix * text.binded;
	vertexPosition = gl_ModelViewMatrix * position;
	vertexNormal = (gl_ModelViewMatrix * normal).xyz;

	gl_Position = gl_ModelViewProjectionMatrix * position;
}

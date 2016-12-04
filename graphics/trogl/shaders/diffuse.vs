#version 130


struct TextureStruct
{
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
        vertexColor = texture2D(text.data, uvMap + text.map);
	vertexColorMix = text.colorMix;
	vertexPosition = gl_ModelViewMatrix * position;
	vertexNormal = (gl_ModelViewMatrix * normal).xyz;

	gl_Position = gl_ModelViewProjectionMatrix * position;
}

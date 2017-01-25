#include "ttsshader.hpp"


TTSShader::TTSShader()
	: Shader("TextureToSceren shader")
{
	_setAttributes({"position", "normal", "uvMap"});
	_loadSubprograms({Shader::pathTo("tts.vs"), Shader::pathTo("tts.fs")});
}


TTSShader::~TTSShader()
{
}


void TTSShader::passComponent(const Component*) const
{
}


void TTSShader::passTextures(const Textures&) const
{
}


void TTSShader::_registerUniforms()
{
	_uniforms.registerate("text");
}


void TTSShader::_passInternalUniforms()
{
}

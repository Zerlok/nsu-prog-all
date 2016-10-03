#include "metamorphose_shader.h"


const std::string MetamorphoseShader::SRC = "\
attribute vec4 position; \
attribute vec4 color; \
uniform vec4 constColor; \
\
void main() {\
 vec3 pos = position.xyz;\
 gl_Position = gl_ModelViewProjectionMatrix * vec4(pos, 1.0);\
 gl_FrontColor = color * constColor;\
}\
";


MetamorphoseShader::MetamorphoseShader()
	: Shader(SRC)
{
}


MetamorphoseShader::~MetamorphoseShader()
{
}

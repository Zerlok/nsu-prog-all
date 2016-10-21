#include "shader.hpp"


#include <logger.hpp>


loggerType loggerInstance = loggerForModule(Logger::Level::DEBUG, Logger::Description::FULL);


const std::string Shader::DEFAULT_VERTEX_SRC = \
	"#version 120\n"
	"attribute vec4 position;\n"
	"attribute vec4 color;\n"
	"void main() {\n"
	"  gl_Position = gl_ModelViewProjectionMatrix * position;\n"
	"  gl_FrontColor = color;\n"
	"}\n";
const std::string Shader::DEFAULT_FRAGMENT_SRC = \
	"#version 120\n"
	"void main() {\n"
	"  gl_FragColor = gl_Color;\n"
	"}\n";


Shader::Shader(const std::string& name,
			   const std::string& vertexSrc,
			   const std::string& fragmentSrc)
	: Component(Component::Type::SHADER, name),
	  _vertexSrc(vertexSrc),
	  _fragmentSrc(fragmentSrc),
	  _isCompiled(false),
	  _shadersCompileCount(0),
	  _glVertexShader(),
	  _glFragmentShader(),
	  _glShaderProgram()
{
}


Shader::Shader(const Shader& sh)
	: Component(sh),
	  _vertexSrc(sh._vertexSrc),
	  _fragmentSrc(sh._fragmentSrc),
	  _isCompiled(false),
	  _shadersCompileCount(0),
	  _glVertexShader(),
	  _glFragmentShader(),
	  _glShaderProgram()
{
}


Shader::Shader(Shader&& sh)
	: Component(sh),
	  _vertexSrc(std::move(sh._vertexSrc)),
	  _fragmentSrc(std::move(sh._fragmentSrc)),
	  _isCompiled(std::move(sh._isCompiled)),
	  _shadersCompileCount(std::move(sh._shadersCompileCount)),
	  _glVertexShader(std::move(sh._glVertexShader)),
	  _glFragmentShader(std::move(sh._glFragmentShader)),
	  _glShaderProgram(std::move(sh._glShaderProgram))
{
	sh._isCompiled = false;
	sh._shadersCompileCount = 0;
	sh._glVertexShader = 0;
	sh._glFragmentShader = 0;
	sh._glShaderProgram = 0;
}


Shader::~Shader()
{
	logModule << "Shaderscompilation count: " << _shadersCompileCount << logEndl;
	logModule << "Removing: (";

	switch (_shadersCompileCount)
	{
		case 3:
			glDetachShader(_glShaderProgram, _glVertexShader);
			glDetachShader(_glShaderProgram, _glFragmentShader);
			glDeleteProgram(_glShaderProgram);
			logModule << "Shader program, ";

		case 2:
			glDeleteShader(_glFragmentShader);
			logModule << "Fragment shader, ";

		case 1:
			glDeleteShader(_glVertexShader);
			logModule << "Vertex shader";
			break;

		case 0:
		default:
			logModule << "none";
			break;
	}

	logModule << ") => shaders deinited." << logEndl;
}


Shader& Shader::operator=(const Shader& sh)
{
	Component::operator=(sh);
	_vertexSrc = sh._vertexSrc;
	_fragmentSrc = sh._fragmentSrc;
	_isCompiled = false;
	_shadersCompileCount = 0;
	_glVertexShader = 0;
	_glFragmentShader = 0;
	_glShaderProgram = 0;

	return (*this);
}


Shader& Shader::operator=(Shader&& sh)
{
	Component::operator=(sh);
	_vertexSrc = std::move(sh._vertexSrc);
	_fragmentSrc = std::move(sh._fragmentSrc);
	_isCompiled = std::move(sh._isCompiled);
	_shadersCompileCount = std::move(sh._shadersCompileCount);
	_glVertexShader = std::move(sh._glVertexShader);
	_glFragmentShader = std::move(sh._glFragmentShader);
	_glShaderProgram = std::move(sh._glShaderProgram);

	sh._isCompiled = false;
	sh._shadersCompileCount = 0;
	sh._glVertexShader = 0;
	sh._glFragmentShader = 0;
	sh._glShaderProgram = 0;

	return (*this);
}


bool Shader::isCompiled() const
{
	return (_isCompiled
			&& (_shadersCompileCount == 3));
}


bool Shader::isValid() const
{
	return (_shadersCompileCount == 3);
}


const GLuint& Shader::getProgram() const
{
	return _glShaderProgram;
}


void Shader::compile()
{
	if (isCompiled())
		return;

	_compileVertexShader();
	_compileFragmentShader();
	_compileShaderProgram();

	if (!isValid())
		return;

	_isCompiled = true;
	initCustomVarsLocations(_glShaderProgram);
}


void Shader::initCustomVarsLocations(const GLuint&)
{
}


void Shader::prepareForRender()
{
}


bool Shader::_compileVertexShader()
{
	int success = 0;
	const char* src = _vertexSrc.data();

	_glVertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_glVertexShader, 1, &(src), NULL);
	glCompileShader(_glVertexShader);
	glGetShaderiv(_glVertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(_glVertexShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in " << getName()
				 << " vertex compilation:\n" << infoLog << logEndl;

		return false;
	}

	++_shadersCompileCount;
	logModule << getName() << " vertex compiled successfuly." << logEndl;
	return true;
}


bool Shader::_compileFragmentShader()
{
	if (_shadersCompileCount < 1)
		return false;

	int success = 0;
	const char* src = _fragmentSrc.data();

	_glFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_glFragmentShader, 1, &(src), NULL);
	glCompileShader(_glFragmentShader);
	glGetShaderiv(_glFragmentShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		const int MAX_INFO_LOG_SIZE = 1024;
		GLchar infoLog[MAX_INFO_LOG_SIZE];
		glGetShaderInfoLog(_glFragmentShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in " << getName()
				 << " fragment compilation:\n" << infoLog << logEndl;

		return false;
	}

	++_shadersCompileCount;
	logModule << getName() << " fragment compiled successfuly." << logEndl;
	return true;
}


bool Shader::_compileShaderProgram()
{
	if (_shadersCompileCount < 2)
		return false;

	int success = 0;
	const int MAX_INFO_LOG_SIZE = 1024;
	GLchar infoLog[MAX_INFO_LOG_SIZE];

	_glShaderProgram = glCreateProgram();
	glAttachShader(_glShaderProgram, _glVertexShader);
	glAttachShader(_glShaderProgram, _glFragmentShader);

	glBindAttribLocation(_glShaderProgram, 0, "position");
	glBindAttribLocation(_glShaderProgram, 1, "colors");

	glLinkProgram(_glShaderProgram);
	glGetProgramiv(_glShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_glShaderProgram, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in shader program linkage: " << infoLog << logEndl;
		return false;
	}

	logModule << "Shader program linked successfuly." << logEndl;

	glValidateProgram(_glShaderProgram);
	glGetProgramiv(_glShaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_glShaderProgram, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in shader program validation: " << infoLog << logEndl;
		return false;
	}

	++_shadersCompileCount;
	logModule << "Shader program is valid. Shaders compilation finished." << logEndl;
	return true;
}

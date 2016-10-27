#include "shader.hpp"


#include <fstream>
#include <sstream>
#include <logger.hpp>
#include "common/utils.h"


loggerModules lModules = loggerForModule(Logger::Level::DEBUG, Logger::Description::FULL);


const std::string Shader::SRC_DIR = path::join(path::dirname(__FILE__), "shaders");
const std::string Shader::DEFAULT_VS_FILE = path::join(Shader::SRC_DIR, "default.vs");
const std::string Shader::DEFAULT_FS_FILE = path::join(Shader::SRC_DIR, "default.fs");


std::string Shader::loadFile(const std::string& filename)
{
	std::stringstream ss;
	std::ifstream in(filename);

	if (!in.is_open())
	{
		logError << "Can't open file: " << filename << logEndl;
		return std::move(ss.str());
	}

	std::string line;
	while (!in.eof())
	{
		std::getline(in, line);
		ss << line << std::endl;
	}

	in.close();
	return std::move(ss.str());
}


Shader Shader::createFromSrc(const std::string& shaderName)
{
	const std::string vsFilename = path::join(SRC_DIR, shaderName + ".vs");
	const std::string fsFilename = path::join(SRC_DIR, shaderName + ".fs");
	return std::move(Shader(shaderName, vsFilename, fsFilename));
}


SharedPointer<Shader> Shader::createPtrFromSrc(const std::string& shaderName)
{
	return std::move(ShaderPtr(new Shader(createFromSrc(shaderName))));
}


Shader::Shader(const std::string& name,
			   const std::string& vsFile,
			   const std::string& fsFile)
	: Component(Component::Type::SHADER, name),
	  _vertexSrc(loadFile(vsFile)),
	  _fragmentSrc(loadFile(fsFile)),
	  _wasCompiled(false),
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
	  _wasCompiled(false),
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
	  _wasCompiled(std::move(sh._wasCompiled)),
	  _shadersCompileCount(std::move(sh._shadersCompileCount)),
	  _glVertexShader(std::move(sh._glVertexShader)),
	  _glFragmentShader(std::move(sh._glFragmentShader)),
	  _glShaderProgram(std::move(sh._glShaderProgram))
{
	sh._wasCompiled = false;
	sh._shadersCompileCount = 0;
	sh._glVertexShader = 0;
	sh._glFragmentShader = 0;
	sh._glShaderProgram = 0;
}


Shader::~Shader()
{
	logModule << "Shaders compilation count: " << _shadersCompileCount << logEndl;
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

	logModule << ") => shaders removed." << logEndl;
}


Shader& Shader::operator=(const Shader& sh)
{
	Component::operator=(sh);
	_vertexSrc = sh._vertexSrc;
	_fragmentSrc = sh._fragmentSrc;
	_wasCompiled = false;
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
	_wasCompiled = std::move(sh._wasCompiled);
	_shadersCompileCount = std::move(sh._shadersCompileCount);
	_glVertexShader = std::move(sh._glVertexShader);
	_glFragmentShader = std::move(sh._glFragmentShader);
	_glShaderProgram = std::move(sh._glShaderProgram);

	sh._wasCompiled = false;
	sh._shadersCompileCount = 0;
	sh._glVertexShader = 0;
	sh._glFragmentShader = 0;
	sh._glShaderProgram = 0;

	return (*this);
}


bool Shader::isValid() const
{
	return (_shadersCompileCount == 3);
}


const bool& Shader::wasCompiled() const
{
	return _wasCompiled;
}


const GLuint& Shader::getProgram() const
{
	return _glShaderProgram;
}


void Shader::compile()
{
	if (wasCompiled())
		return;

	_compileVertexShader();
	_compileFragmentShader();
	_compileShaderProgram();

	if (!isValid())
		return;

	_wasCompiled = true;
	initCustomVarsLocations();
}


void Shader::initCustomVarsLocations()
{
}


void Shader::prepareForRender()
{
}


Shader::Shader(const std::string& name)
	: Component(Component::Type::SHADER, name),
	  _vertexSrc(),
	  _fragmentSrc(),
	  _wasCompiled(false),
	  _shadersCompileCount(0),
	  _glVertexShader(),
	  _glFragmentShader(),
	  _glShaderProgram()
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
	glBindAttribLocation(_glShaderProgram, 1, "color");

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

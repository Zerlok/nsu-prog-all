#include "shader.hpp"


#include <fstream>
#include <sstream>
#include <logger.hpp>
#include "common/utils.hpp"


logger_t loggerModules = loggerModule(Logger::Level::DEBUG, loggerDescriptionFull);


const std::string Shader::SRC_DIR = path::join(path::dirname(path::dirname(__FILE__)), "shaders");
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

	size_t linesCount = 0;
	std::string line;
	while (!in.eof())
	{
		std::getline(in, line);
		ss << line << std::endl;
		++linesCount;
	}
	in.close();

	logDebug << "Shader source code loaded from file: '" << filename
			 << "', (" << linesCount << " lines)."
			 << logEndl;
	return std::move(ss.str());
}


Shader::Shader(const std::string& name,
			   const std::string& vsFile,
			   const std::string& fsFile)
	: Component(Component::Type::SHADER, name),
	  _vertexSrc(loadFile(vsFile)),
	  _fragmentSrc(loadFile(fsFile)),
	  _shadersCompileCount(0),
	  _glVertexShader(),
	  _glFragmentShader(),
	  _glShaderProgram(),
	  _status(Status::NOT_COMPILED)
{
	logDebug << "Shader " << getName()
			 << " created from files (" << vsFile << ", " << fsFile << ')'
			 << logEndl;
}


Shader::Shader(const Shader& sh)
	: Component(sh),
	  _vertexSrc(sh._vertexSrc),
	  _fragmentSrc(sh._fragmentSrc),
	  _shadersCompileCount(0),
	  _glVertexShader(),
	  _glFragmentShader(),
	  _glShaderProgram(),
	  _status(Status::NOT_COMPILED)
{
	logDebug << "Shader " << getName()
			 << " copied from" << sh.getName()
			 << logEndl;
}


Shader::Shader(Shader&& sh)
	: Component(sh),
	  _vertexSrc(std::move(sh._vertexSrc)),
	  _fragmentSrc(std::move(sh._fragmentSrc)),
	  _shadersCompileCount(std::move(sh._shadersCompileCount)),
	  _glVertexShader(std::move(sh._glVertexShader)),
	  _glFragmentShader(std::move(sh._glFragmentShader)),
	  _glShaderProgram(std::move(sh._glShaderProgram)),
	  _status(std::move(sh._status))
{
	sh._shadersCompileCount = 0;
	sh._glVertexShader = 0;
	sh._glFragmentShader = 0;
	sh._glShaderProgram = 0;
	sh._status = Status::NOT_COMPILED;

	logDebug << "Shader " << getName() << " moved." << logEndl;
}


Shader::~Shader()
{
	logDebug << "Shaders compilation count: " << _shadersCompileCount
			 << ", Status: " << _status
			 << ", Removing: (";

	switch (_shadersCompileCount)
	{
		case 3:
			glDetachShader(_glShaderProgram, _glVertexShader);
			glDetachShader(_glShaderProgram, _glFragmentShader);
			glDeleteProgram(_glShaderProgram);
			logDebug << "Shader program, ";

		case 2:
			glDeleteShader(_glFragmentShader);
			logDebug << "Fragment shader, ";

		case 1:
			glDeleteShader(_glVertexShader);
			logDebug << "Vertex shader";
			break;

		case 0:
		default:
			logDebug << "nothing";
			break;
	}

	logDebug << ") => shader removed." << logEndl;
}


Shader& Shader::operator=(const Shader& sh)
{
	Component::operator=(sh);
	_vertexSrc = sh._vertexSrc;
	_fragmentSrc = sh._fragmentSrc;
	_shadersCompileCount = 0;
	_glVertexShader = 0;
	_glFragmentShader = 0;
	_glShaderProgram = 0;
	_status = Status::NOT_COMPILED;

	logDebug << "Shader " << getName() << " copied from " << sh.getName() << logEndl;
	return (*this);
}


Shader& Shader::operator=(Shader&& sh)
{
	Component::operator=(sh);
	_vertexSrc = std::move(sh._vertexSrc);
	_fragmentSrc = std::move(sh._fragmentSrc);
	_shadersCompileCount = std::move(sh._shadersCompileCount);
	_glVertexShader = std::move(sh._glVertexShader);
	_glFragmentShader = std::move(sh._glFragmentShader);
	_glShaderProgram = std::move(sh._glShaderProgram);
	_status = std::move(sh._status);

	sh._shadersCompileCount = 0;
	sh._glVertexShader = 0;
	sh._glFragmentShader = 0;
	sh._glShaderProgram = 0;
	sh._status = Status::NOT_COMPILED;

	logDebug << "Shader " << getName() << " moved." << logEndl;
	return (*this);
}


bool Shader::isCompiled() const
{
	switch (_status)
	{
		case Status::NOT_COMPILED:
			return false;

		case Status::COMPILATION_FAILED:
		case Status::COMPILATION_SUCCESSFUL:
		case Status::NOT_BINDED:
		case Status::BINDED:
		default:
			return true;
	}
}


bool Shader::isCompiledSuccessfuly() const
{
	switch (_status)
	{
		case Status::NOT_COMPILED:
		case Status::COMPILATION_FAILED:
			return false;

		case Status::COMPILATION_SUCCESSFUL:
		case Status::NOT_BINDED:
		case Status::BINDED:
		default:
			return true;
	}
}


bool Shader::isBinded() const
{
	switch (_status)
	{
		case Status::NOT_COMPILED:
		case Status::COMPILATION_FAILED:
		case Status::COMPILATION_SUCCESSFUL:
		case Status::NOT_BINDED:
			return false;

		case Status::BINDED:
		default:
			return true;
	}
}


const Shader::Status& Shader::getStatus() const
{
	return _status;
}


void Shader::compile()
{
	if (isCompiled())
		return;

	_compileVertexShader();
	_compileFragmentShader();
	_compileShaderProgram();

	_status = (_shadersCompileCount == 3)
			? Status::COMPILATION_SUCCESSFUL
			: Status::COMPILATION_FAILED;

	if (!isCompiledSuccessfuly())
		return;

	registerInternalAttributes();
	_status = Status::NOT_BINDED;
}


void Shader::bind()
{
	glUseProgram(_glShaderProgram);
	_status = Status::BINDED;
	passInternalAttributes();
}


void Shader::unbind()
{
	glUseProgram(0);
	_status = Status::NOT_BINDED;
}


bool Shader::registerAttribute(const std::string& name)
{
	Attrs::iterator it = _externalAttributes.find(name);
	if (it != _externalAttributes.end())
		return false;

	Attr glAttr = glGetUniformLocation(_glShaderProgram, name.c_str());
	if (glAttr == -1)
		return false;

	_externalAttributes.insert({name, glAttr});
	return true;
}


Shader::Shader(const std::string& name)
	: Component(Component::Type::SHADER, name),
	  _vertexSrc(),
	  _fragmentSrc(),
	  _shadersCompileCount(0),
	  _glVertexShader(),
	  _glFragmentShader(),
	  _glShaderProgram(),
	  _status(Status::NOT_COMPILED)
{
	logDebug << "Shader " << getName() << " created" << logEndl;
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
	logDebug << getName() << " vertex compiled successfuly." << logEndl;
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
	logDebug << getName() << " fragment compiled successfuly." << logEndl;
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
	glBindAttribLocation(_glShaderProgram, 1, "normal");
	glBindAttribLocation(_glShaderProgram, 2, "color");

	glLinkProgram(_glShaderProgram);
	glGetProgramiv(_glShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_glShaderProgram, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in shader program linkage: " << infoLog << logEndl;
		return false;
	}

	logDebug << "Shader program linked successfuly." << logEndl;

	glValidateProgram(_glShaderProgram);
	glGetProgramiv(_glShaderProgram, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_glShaderProgram, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in shader program validation: " << infoLog << logEndl;
		return false;
	}

	++_shadersCompileCount;
	logDebug << "Shader program is valid. Shaders compilation finished." << logEndl;
	return true;
}


std::ostream& operator<<(std::ostream& out, const Shader::Status& st)
{
	switch (st)
	{
		case Shader::Status::NOT_COMPILED:
			return out << "NOT COMPILED";
		case Shader::Status::COMPILATION_FAILED:
			return out << "COMPILATION FAILED";
		case Shader::Status::COMPILATION_SUCCESSFUL:
			return out << "COMPILATION SUCCESSFUL";
		case Shader::Status::NOT_BINDED:
			return out << "NOT BINDED";
		case Shader::Status::BINDED:
			return out << "BINDED";
	}

	return out;
}


// -------------------------------- UTILS -------------------------------- //

void glAttributeUtils::pass(GLuint glProg, const int& value)
{
	glUniform1i(glProg, value);
}


void glAttributeUtils::pass(GLuint glProg, const float& value)
{
	glUniform1f(glProg, value);
}


void glAttributeUtils::pass(GLuint glProg, const glm::vec2& value)
{
	glUniform2f(glProg, value.x, value.y);
}


void glAttributeUtils::pass(GLuint glProg, const glm::vec3& value)
{
	glUniform3f(glProg, value.x, value.y, value.z);
}


void glAttributeUtils::pass(GLuint glProg, const glm::vec4& value)
{
	glUniform4f(glProg, value.x, value.y, value.z, value.w);
}


void glAttributeUtils::pass(GLuint glProg, const Color& value)
{
	glUniform4f(glProg,
				value.getRedF(),
				value.getGreenF(),
				value.getBlueF(),
				value.getAlphaF());
}

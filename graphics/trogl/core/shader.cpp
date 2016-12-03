#include "shader.hpp"


#include <fstream>
#include <sstream>
#include <logger.hpp>
#include "common/utils.hpp"


logger_t moduleLogger = loggerModule(loggerLInfo, loggerDFull);


const std::string Shader::SRC_DIR = path::join(path::dirname(path::dirname(__FILE__)), "shaders");
const std::string Shader::DEFAULT_VS_FILE = path::join(Shader::SRC_DIR, "default.vs");
const std::string Shader::DEFAULT_GS_FILE = path::join(Shader::SRC_DIR, "default.gs");
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

	logInfo << "Shader source code loaded from file: '" << filename
			<< "', (" << linesCount << " lines)."
			<< logEndl;
	return std::move(ss.str());
}


Shader::Shader(const std::string& name,
			   const std::string& vsFile,
			   const std::string& gsFile,
			   const std::string& fsFile)
	: Component(Component::Type::SHADER, name),
	  _status(Status::NOT_COMPILED),
	  _vertexSrc(loadFile(vsFile)),
	  _geometrySrc(loadFile(gsFile)),
	  _fragmentSrc(loadFile(fsFile)),
	  _glvs(0),
	  _glgs(0),
	  _glfs(0),
	  _glShader(0),
	  _validSubprogramsCount(0),
	  _internalAttributes(),
	  _externalAttributes()
{
	logDebug << "Shader " << getName()
			 << " created from files (" << vsFile << ", " << gsFile << ", " << fsFile << ")."
			 << logEndl;
}


Shader::Shader(const Shader& sh)
	: Component(sh),
	  _status(Status::NOT_COMPILED),
	  _vertexSrc(sh._vertexSrc),
	  _geometrySrc(sh._geometrySrc),
	  _fragmentSrc(sh._fragmentSrc),
	  _glvs(0),
	  _glgs(0),
	  _glfs(0),
	  _glShader(0),
	  _validSubprogramsCount(0),
	  _internalAttributes(),
	  _externalAttributes()
{
	logDebug << "Shader " << getName()
			 << " copied from" << sh.getName()
			 << logEndl;
}


Shader::Shader(Shader&& sh)
	: Component(sh),
	  _status(std::move(sh._status)),
	  _vertexSrc(std::move(sh._vertexSrc)),
	  _geometrySrc(std::move(sh._geometrySrc)),
	  _fragmentSrc(std::move(sh._fragmentSrc)),
	  _glvs(std::move(sh._glvs)),
	  _glgs(std::move(sh._glgs)),
	  _glfs(std::move(sh._glfs)),
	  _glShader(std::move(sh._glShader)),
	  _validSubprogramsCount(std::move(sh._validSubprogramsCount)),
	  _internalAttributes(std::move(sh._internalAttributes)),
	  _externalAttributes(std::move(sh._externalAttributes))
{
	sh._status = Status::NOT_COMPILED;
	sh._glvs = 0;
	sh._glgs = 0;
	sh._glfs = 0;
	sh._glShader = 0;
	sh._validSubprogramsCount = 0;
	sh._internalAttributes.clear();
	sh._externalAttributes.clear();

	logDebug << "Shader " << getName() << " moved." << logEndl;
}


Shader::~Shader()
{
	logDebug << "Shaders compilation count: " << _validSubprogramsCount
			 << ", Status: " << _status
			 << ", Removing: (";

	switch (_validSubprogramsCount)
	{
		case 4:
			glDetachShader(_glShader, _glvs);
			glDetachShader(_glShader, _glfs);
			glDeleteProgram(_glShader);
			logDebug << "Shader program, ";

		case 3:
			glDeleteShader(_glfs);
			logDebug << "FS, ";

		case 2:
			glDeleteShader(_glgs);
			logDebug << "GS, ";

		case 1:
			glDeleteShader(_glvs);
			logDebug << "VS";
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
	_status = Status::NOT_COMPILED;
	_vertexSrc = sh._vertexSrc;
	_geometrySrc = sh._geometrySrc;
	_fragmentSrc = sh._fragmentSrc;
	_glvs = 0;
	_glgs = 0;
	_glfs = 0;
	_glShader = 0;
	_validSubprogramsCount = 0;
	_internalAttributes.clear();
	_externalAttributes.clear();

	logDebug << "Shader " << getName() << " copied from " << sh.getName() << logEndl;
	return (*this);
}


Shader& Shader::operator=(Shader&& sh)
{
	Component::operator=(sh);
	_status = std::move(sh._status);
	_vertexSrc = std::move(sh._vertexSrc);
	_geometrySrc = std::move(sh._geometrySrc);
	_fragmentSrc = std::move(sh._fragmentSrc);
	_glvs = std::move(sh._glvs);
	_glgs = std::move(sh._glgs);
	_glfs = std::move(sh._glfs);
	_validSubprogramsCount = std::move(sh._validSubprogramsCount);
	_glShader = std::move(sh._glShader);

	sh._status = Status::NOT_COMPILED;
	sh._glvs = 0;
	sh._glgs = 0;
	sh._glfs = 0;
	sh._glShader = 0;
	sh._validSubprogramsCount = 0;
	sh._internalAttributes.clear();
	sh._externalAttributes.clear();

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


bool Shader::isCompiledSuccessfully() const
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

	_compileSubprogram(_glvs, _vertexSrc, GL_VERTEX_SHADER);
//	_compileSubprogram(_glgs, _geometrySrc, GL_GEOMETRY_SHADER);
	_compileSubprogram(_glfs, _fragmentSrc, GL_FRAGMENT_SHADER);
	_linkShaderProgram();

	_status = (_validSubprogramsCount == 3)
			? Status::COMPILATION_SUCCESSFUL
			: Status::COMPILATION_FAILED;

	if (!isCompiledSuccessfully())
		return;

	_internalAttributes.setShaderProgram(_glShader);
	_externalAttributes.setShaderProgram(_glShader);
	_registerAttributes();

	_status = Status::NOT_BINDED;
}


void Shader::bind()
{
	glUseProgram(_glShader);
	_status = Status::BINDED;

	_passInternalAttributes();
}


void Shader::unbind()
{
	glUseProgram(0);
	_status = Status::NOT_BINDED;
}


Shader::Shader(const std::string& name)
	: Component(Component::Type::SHADER, name),
	  _status(Status::NOT_COMPILED),
	  _vertexSrc(),
	  _geometrySrc(),
	  _fragmentSrc(),
	  _glvs(),
	  _glgs(),
	  _glfs(),
	  _glShader(),
	  _validSubprogramsCount(0),
	  _internalAttributes(),
	  _externalAttributes()
{
	logDebug << "Shader " << getName() << " created." << logEndl;
}


bool Shader::_compileSubprogram(GLuint& subProg,
								const std::string& codeSrc,
								const GLenum& type)
{
	int success = 0;
	const int MAX_INFO_LOG_SIZE = 1024;
	GLchar infoLog[MAX_INFO_LOG_SIZE];

	const char* src = codeSrc.data();

	subProg = glCreateShader(type);
	glShaderSource(subProg, 1, &(src), NULL);
	glCompileShader(subProg);
	glGetShaderiv(subProg, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(subProg, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in " << getName()
				 << " subprogram compilation: " << std::endl << infoLog
				 << logEndl;
		return false;
	}

	++_validSubprogramsCount;
	logDebug << getName() << " subprogram compiled successfuly." << logEndl;
	return true;
}


bool Shader::_linkShaderProgram()
{
	int success = 0;
	const int MAX_INFO_LOG_SIZE = 1024;
	GLchar infoLog[MAX_INFO_LOG_SIZE];

	_glShader = glCreateProgram();
	glAttachShader(_glShader, _glvs);
//	glAttachShader(_glShader, _glgs);
	glAttachShader(_glShader, _glfs);

	glBindAttribLocation(_glShader, 0, "position");
	glBindAttribLocation(_glShader, 1, "normal");
	glBindAttribLocation(_glShader, 2, "color");

	glLinkProgram(_glShader);
	glGetProgramiv(_glShader, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_glShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in shader program linkage: " << infoLog << logEndl;
		return false;
	}

	logDebug << "Shader program linked successfuly." << logEndl;

	glValidateProgram(_glShader);
	glGetProgramiv(_glShader, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_glShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in shader program validation: " << infoLog << logEndl;
		return false;
	}

	++_validSubprogramsCount;
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


const Attributes::Attr Attributes::NOT_FOUND = Attributes::Attr(-1);


Attributes::Attributes()
	: _attrsMap(),
	  _glShaderProg()
{
}


Attributes::Attributes(const Attributes& attrs)
	: _attrsMap(attrs._attrsMap),
	  _glShaderProg(attrs._glShaderProg)
{
}


Attributes::Attributes(Attributes&& attrs)
	: _attrsMap(std::move(attrs._attrsMap)),
	  _glShaderProg(std::move(attrs._glShaderProg))
{
}


Attributes::~Attributes()
{
}


Attributes& Attributes::operator=(const Attributes& attrs)
{
	_attrsMap = attrs._attrsMap;
	_glShaderProg = attrs._glShaderProg;

	return (*this);
}


Attributes& Attributes::operator=(Attributes&& attrs)
{
	_attrsMap = std::move(attrs._attrsMap);
	_glShaderProg = std::move(attrs._glShaderProg);

	return (*this);
}


void Attributes::clear()
{
	_attrsMap.clear();
}


void Attributes::setShaderProgram(const GLuint& glProg)
{
	_glShaderProg = glProg;
}


bool Attributes::registerate(const std::string& name)
{
	AttrsMap::iterator it = _attrsMap.find(name);
	if (it != _attrsMap.end())
		return false;

	Attr glAttr = glGetUniformLocation(_glShaderProg, name.c_str());
	if (glAttr == NOT_FOUND)
		return false;

	_attrsMap.insert({name, glAttr});
	return true;
}


bool Attributes::pass(const std::string& name,
					  const float& val1,
					  const float& val2,
					  const float& val3,
					  const float& val4) const
{
	return pass<glm::vec4>(name, glm::vec4(val1, val2, val3, val4));
}


void Attributes::_pass(const GLuint& glLoc, const int& value)
{
	glUniform1i(glLoc, value);
}


void Attributes::_pass(const GLuint& glLoc, const float& value)
{
	glUniform1f(glLoc, value);
}


void Attributes::_pass(const GLuint& glLoc, const glm::vec2& value)
{
	glUniform2f(glLoc, value.x, value.y);
}


void Attributes::_pass(const GLuint& glLoc, const glm::vec3& value)
{
	glUniform3f(glLoc, value.x, value.y, value.z);
}


void Attributes::_pass(const GLuint& glLoc, const glm::vec4& value)
{
	glUniform4f(glLoc, value.x, value.y, value.z, value.w);
}


void Attributes::_pass(const GLuint& glLoc, const Color& value)
{
	glUniform4f(glLoc,
				value.getRedF(),
				value.getGreenF(),
				value.getBlueF(),
				value.getAlphaF());
}

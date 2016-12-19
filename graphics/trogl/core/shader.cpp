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


Shader::Shader(const std::string& name,
			   const std::vector<std::string>& filenames)
	: Component(Component::Type::SHADER, name),
	  _status(Status::NOT_COMPILED),
	  _glShader(0),
	  _subprograms({}),
	  _internalAttributes(),
	  _externalAttributes()
{
	_loadSubprograms(filenames);
	logDebug << "Shader " << getName()
			 << " created from files " << filenames << ")."
			 << logEndl;
}


Shader::Shader(const Shader& sh)
	: Component(sh),
	  _status(Status::NOT_COMPILED),
	  _glShader(0),
	  _subprograms(sh._subprograms),
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
	  _glShader(std::move(sh._glShader)),
	  _subprograms(std::move(sh._subprograms)),
	  _internalAttributes(std::move(sh._internalAttributes)),
	  _externalAttributes(std::move(sh._externalAttributes))
{
	sh._status = Status::NOT_COMPILED;
	sh._glShader = 0;
	sh._internalAttributes.clear();
	sh._externalAttributes.clear();

	logDebug << "Shader " << getName() << " moved." << logEndl;
}


Shader::~Shader()
{
	for (Subprogram& prog : _subprograms)
		prog.unlink(_glShader);

	glDeleteProgram(_glShader);

	logDebug << getName() << " removed." << logEndl;
}


Shader& Shader::operator=(const Shader& sh)
{
	Component::operator=(sh);
	_status = Status::NOT_COMPILED;
	_subprograms = sh._subprograms;
	_glShader = 0;
	_internalAttributes.clear();
	_externalAttributes.clear();

	logDebug << "Shader " << getName() << " copied from " << sh.getName() << logEndl;
	return (*this);
}


Shader& Shader::operator=(Shader&& sh)
{
	Component::operator=(sh);
	_status = std::move(sh._status);
	_subprograms = std::move(sh._subprograms);
	_glShader = std::move(sh._glShader);

	sh._status = Status::NOT_COMPILED;
	sh._glShader = 0;
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

	for (Subprogram& prog : _subprograms)
		prog.compile();

	_status = (_linkShaderProgram())
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
	  _glShader(),
	  _subprograms({}),
	  _internalAttributes(),
	  _externalAttributes()
{
	logDebug << "Shader " << getName() << " created." << logEndl;
}


void Shader::_loadSubprograms(const std::vector<std::string>& filenames)
{
	for (const std::string& filename : filenames)
		_subprograms.push_back(Subprogram::loadFile(filename));
}


bool Shader::_linkShaderProgram()
{
	int success = 0;
	const int MAX_INFO_LOG_SIZE = 1024;
	GLchar infoLog[MAX_INFO_LOG_SIZE];

	_glShader = glCreateProgram();
	for (Subprogram& prog : _subprograms)
		prog.link(_glShader);

	glBindAttribLocation(_glShader, 0, "position");
	glBindAttribLocation(_glShader, 1, "normal");
	glBindAttribLocation(_glShader, 2, "uvMap");

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


// -------------------------------- Shader Attributes -------------------------------- //


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
	{
		logWarning << "Uniform: " << name << " were not found!" << logEndl;
		return false;
	}

	_attrsMap.insert({name, {glAttr}});
	return true;
}


bool Attributes::registerateArray(const std::string& name, const size_t& len)
{
	AttrsMap::iterator it = _attrsMap.find(name);
	if (it != _attrsMap.end())
		return false;

	size_t idxPos = name.find("[]");
	if (idxPos == std::string::npos)
		return false;

	const std::string left = name.substr(0, idxPos+1);
	const std::string right = name.substr(idxPos+1, name.length() - idxPos - 1);

	Attrs glAttrs;
	std::string locName;
	std::stringstream ss;
	for (size_t i = 0; i < len; ++i)
	{
		ss.str("");
		ss << left << i << right;
		locName = ss.str();

		Attr glAttr = glGetUniformLocation(_glShaderProg, locName.c_str());
		if (glAttr == NOT_FOUND)
			break;

		glAttrs.push_back(glAttr);
	}

	if (glAttrs.size() < len)
		logWarning << "Uniform: " << name << ", "
				   << glAttrs.size() << '/' << len << " array attributes were located!"
				   << logEndl;

	_attrsMap.insert({name, glAttrs});
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


void Attributes::_pass(const GLuint& glLoc, const unsigned int& value)
{
	glUniform1ui(glLoc, value);
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


// -------------------------------- Shader::Subprogram -------------------------------- //

Shader::Subprogram Shader::Subprogram::loadFile(const std::string& filename)
{
	Subprogram subprog;
	std::stringstream ss;
	std::ifstream in(filename);

	if (!in.is_open())
	{
		logError << "Can't open file: " << filename << logEndl;
		return std::move(subprog);
	}

	size_t linesCount = 0;
	std::string line;
	while (!in.eof())
	{
		std::getline(in, line);
		ss << line << std::endl;

		if (linesCount == 0)
		{
			size_t pos = line.find(' ') + 1;
			subprog.version = line.substr(pos, line.size() - pos);
		}

		++linesCount;
	}
	in.close();

	subprog.getTypeFromFilename(filename);
	subprog.src = ss.str();

	logInfo << "Shader source code loaded from file: '" << filename
			<< "', (" << linesCount << " lines)."
			<< logEndl;
	return std::move(subprog);
}


Shader::Subprogram::Subprogram()
	: id(0),
	  type(0),
	  src(),
	  version(),
	  valid(false)
{
}


Shader::Subprogram::Subprogram(const Shader::Subprogram& sp)
	: id(0),
	  type(sp.type),
	  src(sp.src),
	  version(sp.version),
	  valid(false)
{
}


Shader::Subprogram::Subprogram(Shader::Subprogram&& sp)
	: id(std::move(sp.id)),
	  type(std::move(sp.type)),
	  src(std::move(sp.src)),
	  version(std::move(sp.version)),
	  valid(std::move(sp.valid))
{
}


Shader::Subprogram::~Subprogram()
{
	if (!valid)
		return;

	glDeleteShader(id);
}


Shader::Subprogram& Shader::Subprogram::operator=(const Shader::Subprogram& sp)
{
	id = 0;
	type = sp.type;
	src = sp.src;
	version = sp.version;
	valid = false;

	return (*this);
}


Shader::Subprogram& Shader::Subprogram::operator=(Shader::Subprogram&& sp)
{
	id = std::move(sp.id);
	type = std::move(sp.type);
	src = std::move(sp.src);
	version = std::move(sp.version);
	valid = std::move(sp.valid);

	return (*this);
}


bool Shader::Subprogram::compile()
{
	int success = 0;
	const int MAX_INFO_LOG_SIZE = 1024;
	GLchar infoLog[MAX_INFO_LOG_SIZE];

	const char* code = src.data();

	id = glCreateShader(type);
	glShaderSource(id, 1, &(code), NULL);
	glCompileShader(id);
	glGetShaderiv(id, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(id, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in " << type << " subprogram compilation: " << infoLog << logEndl;
		return false;
	}

	valid = true;
	logDebug << "Subprogram compiled successfuly." << logEndl;
	return true;
}


void Shader::Subprogram::getTypeFromFilename(const std::string& filename)
{
	const std::string ext = path::extension(filename);

	if (ext == "vs")
		type = GL_VERTEX_SHADER;
	else if (ext == "gs")
		type = GL_GEOMETRY_SHADER;
	else if (ext == "fs")
		type = GL_FRAGMENT_SHADER;
}


void Shader::Subprogram::link(GLuint& glShader)
{
	if (!valid)
		return;

	glAttachShader(glShader, id);
}


void Shader::Subprogram::unlink(GLuint& glShader)
{
	if (!valid)
		return;

	glDetachShader(glShader, id);
}

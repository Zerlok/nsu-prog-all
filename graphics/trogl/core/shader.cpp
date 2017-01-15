#include "shader.hpp"


#include <fstream>
#include <sstream>
#include <logger.hpp>
#include "common/utils.hpp"


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


const std::string Shader::SRC_DIR = path::join(path::dirname(path::dirname(__FILE__)), "shaders");
const std::string Shader::DEFAULT_VS_FILE = path::join(Shader::SRC_DIR, "default.vs");
const std::string Shader::DEFAULT_GS_FILE = path::join(Shader::SRC_DIR, "default.gs");
const std::string Shader::DEFAULT_FS_FILE = path::join(Shader::SRC_DIR, "default.fs");


Shader::Shader(const std::string& name)
	: Component("SHADER", name),
	  _status(Status::NOT_COMPILED),
	  _glShader(0),
	  _subprograms({}),
	  _uniforms()
{
	logDebug << "Shader " << getName() << " created (inherited)." << logEndl;
}


Shader::Shader(const std::string& name,
			   const std::vector<std::string>& filenames)
	: Component("SHADER", name),
	  _status(Status::NOT_COMPILED),
	  _glShader(0),
	  _subprograms({}),
	  _uniforms()
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
	  _uniforms()
{
	logDebug << "Shader " << getName()
			 << " copied from " << sh.getName()
			 << logEndl;
}


Shader::Shader(Shader&& sh)
	: Component(std::move(sh)),
	  _status(std::move(sh._status)),
	  _glShader(std::move(sh._glShader)),
	  _subprograms(std::move(sh._subprograms)),
	  _uniforms(std::move(sh._uniforms))
{
	sh._status = Status::NOT_COMPILED;
	sh._glShader = 0;

	logDebug << "Shader " << getName() << " moved." << logEndl;
}


Shader::~Shader()
{
	for (Subprogram& prog : _subprograms)
		prog.unlink(_glShader);

	if (_glShader != 0)
		glDeleteProgram(_glShader);

	logDebug << getName() << " removed." << logEndl;
}


Shader& Shader::operator=(const Shader& sh)
{
	_status = Status::NOT_COMPILED;
	_glShader = 0;
	_subprograms = sh._subprograms;
	_uniforms.clear();

	logDebug << "Shader " << getName() << " copied from " << sh.getName() << logEndl;
	return (*this);
}


Shader& Shader::operator=(Shader&& sh)
{
	_status = std::move(sh._status);
	_glShader = std::move(sh._glShader);
	_subprograms = std::move(sh._subprograms);
	_uniforms = std::move(sh._uniforms);

	sh._status = Status::NOT_COMPILED;
	sh._glShader = 0;

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

	_uniforms.setShaderProgram(_glShader);
	_registerGLUniforms();
	_registerUniforms();

	_status = Status::NOT_BINDED;
}


void Shader::bind()
{
	glUseProgram(_glShader);
	_status = Status::BINDED;

	_passInternalUniforms();
}


void Shader::unbind()
{
	glUseProgram(0);
	_status = Status::NOT_BINDED;
}


void Shader::passBasicMatrices(const glm::mat4x4& mw,
							   const glm::mat4x4& mv,
							   const glm::mat4x4& mp) const
{
	_uniforms.pass("MW", mw);
	_uniforms.pass("MV", mv);
	_uniforms.pass("MP", mp);
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
		logError << "Error in shader program linkage:" << std::endl
				 << infoLog << logEndl;
		return false;
	}

	logDebug << "Shader program linked successfuly." << logEndl;

	glValidateProgram(_glShader);
	glGetProgramiv(_glShader, GL_VALIDATE_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(_glShader, MAX_INFO_LOG_SIZE, NULL, infoLog);
		logError << "Error in shader program validation:"<< std::endl
				 << infoLog << logEndl;
		return false;
	}

	logDebug << "Shader program is valid. Shaders compilation finished." << logEndl;
	return true;
}


void Shader::_registerGLUniforms()
{
	_uniforms.registerate("MW");
	_uniforms.registerate("MV");
	_uniforms.registerate("MP");
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
			<< "', (lines: " << linesCount << ", GLSL: " << subprog.version
			<< ")."
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
		logError << "Error in " << type << " subprogram compilation:" << std::endl
				 << infoLog << logEndl;
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


// -------------------------------- Shader Uniforms -------------------------------- //

const Shader::Uniforms::UniLoc Shader::Uniforms::NOT_FOUND(-1);


Shader::Uniforms::Uniforms()
	: _uniLocationsMap(),
	  _glShaderProg()
{
}


Shader::Uniforms::Uniforms(const Shader::Uniforms& unis)
	: _uniLocationsMap(unis._uniLocationsMap),
	  _glShaderProg(unis._glShaderProg)
{
}


Shader::Uniforms::Uniforms(Shader::Uniforms&& unis)
	: _uniLocationsMap(std::move(unis._uniLocationsMap)),
	  _glShaderProg(std::move(unis._glShaderProg))
{
	unis._glShaderProg = 0;
}


Shader::Uniforms::~Uniforms()
{
}


Shader::Uniforms& Shader::Uniforms::operator=(const Shader::Uniforms& unis)
{
	_uniLocationsMap = unis._uniLocationsMap;
	_glShaderProg = unis._glShaderProg;

	return (*this);
}


Shader::Uniforms& Shader::Uniforms::operator=(Shader::Uniforms&& unis)
{
	_uniLocationsMap = std::move(unis._uniLocationsMap);
	_glShaderProg = std::move(unis._glShaderProg);

	unis._glShaderProg = 0;

	return (*this);
}


void Shader::Uniforms::clear()
{
	_uniLocationsMap.clear();
	_glShaderProg = 0;
}


void Shader::Uniforms::setShaderProgram(const GLuint& glProg)
{
	_glShaderProg = glProg;
}


bool Shader::Uniforms::registerate(const std::string& name)
{
	UniLocsMap::iterator it = _uniLocationsMap.find(name);
	if (it != _uniLocationsMap.end())
		return false;

	UniLoc glLoc = glGetUniformLocation(_glShaderProg, name.c_str());
	if (glLoc == NOT_FOUND)
	{
		logWarning << "Uniform: " << name << " were not found!" << logEndl;
		return false;
	}

	_uniLocationsMap.insert({name, {glLoc}});
	return true;
}


bool Shader::Uniforms::registerateArray(const std::string& name, const size_t& len)
{
	UniLocsMap::iterator it = _uniLocationsMap.find(name);
	if (it != _uniLocationsMap.end())
		return false;

	size_t idxPos = name.find("[]");
	if (idxPos == std::string::npos)
		return false;

	const std::string leftPartName = name.substr(0, idxPos+1);
	const std::string rightPartName = name.substr(idxPos+1, name.length() - idxPos - 1);

	UniLoc glLoc;
	UniLocs glLocs;
	std::string locName;
	std::stringstream ss;
	for (size_t i = 0; i < len; ++i)
	{
		ss.str("");
		ss << leftPartName << i << rightPartName;
		locName = ss.str();

		glLoc = glGetUniformLocation(_glShaderProg, locName.c_str());
		if (glLoc == NOT_FOUND)
			break;

		glLocs.push_back(glLoc);
	}

	if (glLocs.size() < len)
		logWarning << "Uniform: " << name << ", "
				   << glLocs.size() << '/' << len << " array attributes were located!"
				   << logEndl;

	_uniLocationsMap.insert({name, glLocs});
	return true;
}


bool Shader::Uniforms::pass(const std::string& name,
					  const float& val1,
					  const float& val2,
					  const float& val3,
					  const float& val4) const
{
	return pass<glm::vec4>(name, glm::vec4(val1, val2, val3, val4));
}


void Shader::Uniforms::_pass(const GLuint& glLoc, const int& value)
{
	glUniform1i(glLoc, value);
}


void Shader::Uniforms::_pass(const GLuint& glLoc, const unsigned int& value)
{
	glUniform1ui(glLoc, value);
}


void Shader::Uniforms::_pass(const GLuint& glLoc, const float& value)
{
	glUniform1f(glLoc, value);
}


void Shader::Uniforms::_pass(const GLuint& glLoc, const glm::vec2& value)
{
	glUniform2f(glLoc, value.x, value.y);
}


void Shader::Uniforms::_pass(const GLuint& glLoc, const glm::vec3& value)
{
	glUniform3f(glLoc, value.x, value.y, value.z);
}


void Shader::Uniforms::_pass(const GLuint& glLoc, const glm::vec4& value)
{
	glUniform4f(glLoc, value.x, value.y, value.z, value.w);
}


void Shader::Uniforms::_pass(const GLuint& glLoc, const glm::mat2x2& value)
{
	glUniformMatrix2fv(glLoc, 1, GL_FALSE, &value[0][0]);
}


void Shader::Uniforms::_pass(const GLuint& glLoc, const glm::mat3x3& value)
{
	glUniformMatrix3fv(glLoc, 1, GL_FALSE, &value[0][0]);
}


void Shader::Uniforms::_pass(const GLuint& glLoc, const glm::mat4x4& value)
{
	glUniformMatrix4fv(glLoc, 1, GL_FALSE, &value[0][0]);
}


void Shader::Uniforms::_pass(const GLuint& glLoc, const Color& value)
{
	glUniform4f(glLoc,
				value.getRedF(),
				value.getGreenF(),
				value.getBlueF(),
				value.getAlphaF());
}

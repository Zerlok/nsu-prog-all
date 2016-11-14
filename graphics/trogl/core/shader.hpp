#ifndef __SHADER_HPP__
#define __SHADER_HPP__


#include <string>
#include <unordered_map>
#include <sharedpointer.h>
#include "common/color.hpp"
#include "opengls.hpp"
#include "component.hpp"
#include "object.hpp"


namespace glAttributeUtils
{
	void pass(GLuint glProg, const int& value);
	void pass(GLuint glProg, const float& value);
	void pass(GLuint glProg, const glm::vec2& value);
	void pass(GLuint glProg, const glm::vec3& value);
	void pass(GLuint glProg, const glm::vec4& value);
	void pass(GLuint glProg, const Color& value);
};


class Shader : public Component
{
	public:
		// Inner classes.
		enum class Status
		{
			NOT_COMPILED = 0,
			COMPILATION_FAILED,
			COMPILATION_SUCCESSFUL,
			NOT_BINDED,
			BINDED,
		};

		using Attr = GLuint;
		using Attrs = std::unordered_map<std::string, Attr>;

		// Static fields.
		static const std::string SRC_DIR;
		static const std::string DEFAULT_VS_FILE;
		static const std::string DEFAULT_FS_FILE;

		// Static methods.
		static std::string loadFile(const std::string& filename);

		// Constructors / Destructor.
		Shader(const std::string& name,
			   const std::string& vsFile = DEFAULT_VS_FILE,
			   const std::string& fsFile = DEFAULT_FS_FILE);
		Shader(const Shader& sh);
		Shader(Shader&& sh);
		virtual ~Shader();

		// Operators.
		Shader& operator=(const Shader& sh);
		Shader& operator=(Shader&& sh);

		// Methods.
		bool isCompiled() const;
		bool isCompiledSuccessfuly() const;
		bool isBinded() const;
		const Status& getStatus() const;

		void compile();
		void bind();
		void unbind();

		bool registerAttribute(const std::string& name);
		template<class T>
		bool passAttribute(const std::string& name,
						   const T& value)
		{
			Attrs::iterator it = _externalAttributes.find(name);
			if (it == _externalAttributes.end())
				return false;

			glAttributeUtils::pass(_glShaderProgram, value);
			return true;
		}

		// Virtual methods.
		virtual void passObject(Object const*) = 0;
		virtual void registerInternalAttributes() = 0;
		virtual void passInternalAttributes() = 0;

	protected:
		// Constructor.
		Shader(const std::string& name);

		// Fields.
		std::string _vertexSrc;
		std::string _fragmentSrc;

		size_t _shadersCompileCount;
		GLuint _glVertexShader;		// Vertices rendering
		GLuint _glFragmentShader;	// Faces rendering.
		GLuint _glShaderProgram;	// Total shadering program.

		Attrs _externalAttributes;

	private:
		// Fields.
		Status _status;

		// Methods.
		bool _compileVertexShader();
		bool _compileFragmentShader();
		bool _compileShaderProgram();
};

using ShaderPtr = SharedPointer<Shader>;

std::ostream& operator<<(std::ostream& out, const Shader::Status& st);


#endif // __SHADER_HPP__

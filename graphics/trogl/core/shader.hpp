#ifndef __SHADER_HPP__
#define __SHADER_HPP__


#include <string>
#include <vector>
#include <unordered_map>
#include <sharedpointer.h>
#include "common/color.hpp"
#include "opengls.hpp"
#include "component.hpp"
#include "object.hpp"


class Attributes
{
	public:
		// Inner classes.
		using Attr = GLuint;
		using AttrsMap = std::unordered_map<std::string, Attr>;

		// Constructors / Destructor.
		Attributes();
		Attributes(const Attributes& attrs);
		Attributes(Attributes&& attrs);
		~Attributes();

		// Operators.
		Attributes& operator=(const Attributes& attrs);
		Attributes& operator=(Attributes&& attrs);

		// Methods.
		void clear();
		void setShaderProgram(const GLuint& glProg);
		bool registerate(const std::string& name);

		template<class T>
		bool pass(const std::string& name, const T& value) const
		{
			AttrsMap::const_iterator it = _attrsMap.find(name);
			if (it == _attrsMap.cend())
				return false;

			_pass((*it).second, value);
			return true;
		}

		bool pass(const std::string& name,
				  const float& val1,
				  const float& val2,
				  const float& val3,
				  const float& val4) const;

	private:
		// Static fields.
		static const Attr NOT_FOUND;

		// Static methods.
		static void _pass(const GLuint& loc, const int& value);
		static void _pass(const GLuint& loc, const float& value);
		static void _pass(const GLuint& loc, const glm::vec2& value);
		static void _pass(const GLuint& loc, const glm::vec3& value);
		static void _pass(const GLuint& loc, const glm::vec4& value);
		static void _pass(const GLuint& loc, const Color& value);

		// Fields.
		AttrsMap _attrsMap;
		GLuint _glShaderProg;
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

		class Subprogram
		{
			public:
				// Static methods.
				static Subprogram loadFile(const std::string& filename);

				// Constructors / Destructor.
				Subprogram();
				Subprogram(const Subprogram& sp);
				Subprogram(Subprogram&& sp);
				~Subprogram();

				// Operators.
				Subprogram& operator=(const Subprogram& sp);
				Subprogram& operator=(Subprogram&& sp);

				// Methods.
				bool compile();
				void getTypeFromFilename(const std::string& filename);
				void link(GLuint& glShader);
				void unlink(GLuint& glShader);

			private:
				// Fields.
				GLuint id;
				GLenum type;
				std::string src;
				std::string version;
				bool valid;
		};

		using Attr = Attributes::Attr;

		// Static fields.
		static const std::string SRC_DIR;
		static const std::string DEFAULT_VS_FILE;
		static const std::string DEFAULT_GS_FILE;
		static const std::string DEFAULT_FS_FILE;

		// Constructors / Destructor.
		Shader(const std::string& name,
			   const std::vector<std::string>& filenames);
		Shader(const Shader& sh);
		Shader(Shader&& sh);
		virtual ~Shader();

		// Operators.
		Shader& operator=(const Shader& sh);
		Shader& operator=(Shader&& sh);

		// Methods.
		bool isCompiled() const;
		bool isCompiledSuccessfully() const;
		bool isBinded() const;
		const Status& getStatus() const;

		void compile();
		void bind();
		void unbind();

		template<class T>
		bool passAttribute(const std::string& name,
						   const T& value) const
		{
			return _externalAttributes.pass(name, value);
		}

		// Virtual methods.
		virtual void passComponent(Component const*) = 0;
		virtual void passObject(Object const*) = 0;

	protected:
		// Constructor.
		Shader(const std::string& name);
		void _loadSubprograms(const std::vector<std::string>& filenames);

	private:
		// Fields.
		Status _status;

	protected:
		// Fields.
		GLuint _glShader;	// Total shader program.
		std::vector<Subprogram> _subprograms;

		Attributes _internalAttributes;
		Attributes _externalAttributes;

		// Virtual methods.
		virtual void _registerAttributes() = 0;
		virtual void _passInternalAttributes() = 0;

	private:
		// Methods.
		bool _linkShaderProgram();
};

using ShaderPtr = SharedPointer<Shader, Component>;

std::ostream& operator<<(std::ostream& out, const Shader::Status& st);


#endif // __SHADER_HPP__

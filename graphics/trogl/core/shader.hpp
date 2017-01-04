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
#include "texture.hpp"


class Uniforms
{
	public:
		// Inner classes.
		using UniLoc = GLuint;
		using UniLocs = std::vector<UniLoc>;
		using UniLocsMap = std::unordered_map<std::string, UniLocs>;

		// Constructors / Destructor.
		Uniforms();
		Uniforms(const Uniforms& unis);
		Uniforms(Uniforms&& unis);
		~Uniforms();

		// Operators.
		Uniforms& operator=(const Uniforms& unis);
		Uniforms& operator=(Uniforms&& unis);

		// Methods.
		void clear();
		void setShaderProgram(const GLuint& glProg);
		bool registerate(const std::string& name);
		bool registerateArray(const std::string& name, const size_t& len);

		template<class T>
		bool pass(const std::string& name, const T& value) const
		{
			UniLocsMap::const_iterator it = _uniLocationsMap.find(name);
			if (it == _uniLocationsMap.cend())
				return false;

			_pass((*it).second.front(), value);
			return true;
		}

		template<class T>
		bool passEl(const std::string& name, const size_t& idx, const T& value) const
		{
			UniLocsMap::const_iterator it = _uniLocationsMap.find(name);
			if (it == _uniLocationsMap.cend())
				return false;

			const UniLocs& locations = (*it).second;
			if (locations.size() <= idx)
				return false;

			_pass(locations[idx], value);
			return true;
		}

		template<class T>
		bool passArray(const std::string& name, const std::vector<T> values) const
		{
			UniLocsMap::const_iterator it = _uniLocationsMap.find(name);
			if (it == _uniLocationsMap.cend())
				return false;

			const UniLocs& locations = (*it).second;
			for (size_t i = 0; i < std::min(locations.size(), values.size()); ++i)
				_pass(locations[i], values[i]);

			return true;
		}

		bool pass(const std::string& name,
				  const float& val1,
				  const float& val2,
				  const float& val3,
				  const float& val4) const;

	private:
		// Static fields.
		static const UniLoc NOT_FOUND;

		// Static methods.
		static void _pass(const GLuint& loc, const int& value);
		static void _pass(const GLuint& loc, const unsigned int& value);
		static void _pass(const GLuint& loc, const float& value);
		static void _pass(const GLuint& loc, const glm::vec2& value);
		static void _pass(const GLuint& loc, const glm::vec3& value);
		static void _pass(const GLuint& loc, const glm::vec4& value);
		static void _pass(const GLuint& loc, const glm::mat2x2& value);
		static void _pass(const GLuint& loc, const glm::mat3x3& value);
		static void _pass(const GLuint& loc, const glm::mat4x4& value);
		static void _pass(const GLuint& loc, const Color& value);

		// Fields.
		UniLocsMap _uniLocationsMap;
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
		bool passUniform(const std::string& name,
						 const T& value) const
		{
			return _uniforms.pass(name, value);
		}

		// Virtual methods.
		virtual void passComponent(const Component*) const = 0;
		virtual void passTextures(const Textures&) const = 0;

	protected:
		// Constructor.
		Shader(const std::string& name);

		// Methods.
		void _loadSubprograms(const std::vector<std::string>& filenames);

		// Virtual methods.
		virtual void _registerUniforms() = 0;
		virtual void _passInternalUniforms() = 0;

	private:
		// Fields.
		Status _status;

		// Methods.
		bool _linkShaderProgram();
		void _registerGLUniforms();

	protected:
		// Fields.
		GLuint _glShader;	// Total shader program.
		std::vector<Subprogram> _subprograms;
		Uniforms _uniforms;

};

using ShaderPtr = SharedPointer<Shader, Component>;

std::ostream& operator<<(std::ostream& out, const Shader::Status& st);


#endif // __SHADER_HPP__

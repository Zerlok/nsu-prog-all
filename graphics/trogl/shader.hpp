#ifndef __SHADER_HPP__
#define __SHADER_HPP__


#include <string>
#include <sharedpointer.h>
#include "opengls.hpp"
#include "component.hpp"
#include "object.hpp"


class Shader : public Component
{
	public:
		// Inner classes.
		enum class Status
		{
			NOT_COMPILED = 0,
			COMPILATION_FAILED,
			COMPILATION_SUCCESSFUL,
		};

		// Static fields.
		static const std::string SRC_DIR;
		static const std::string DEFAULT_VS_FILE;
		static const std::string DEFAULT_FS_FILE;

		// Static methods.
		static std::string loadFile(const std::string& filename);
		static Shader createFromSrc(const std::string& shaderName);
		static SharedPointer<Shader> createPtrFromSrc(const std::string& shaderName);

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
		const Status& getStatus() const;
		const GLuint& getProgram() const;

		void compile();

		// Virtual methods.
		virtual void initCustomVarsLocations();
		virtual void passObject(const Object*);
		virtual void prepareForRender();

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

	private:
		// Fields.
		Status _status;

		// Methods.
		bool _compileVertexShader();
		bool _compileFragmentShader();
		bool _compileShaderProgram();
};

using ShaderPtr = SharedPointer<Shader>;


#endif // __SHADER_HPP__

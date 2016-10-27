#ifndef __SHADER_HPP__
#define __SHADER_HPP__


#include <string>
#include <sharedpointer.h>
#include "opengls.hpp"
#include "component.hpp"


class Shader : public Component
{
	public:
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
		bool isValid() const;
		const bool& wasCompiled() const;
		const GLuint& getProgram() const;

		void compile();

		// Virtual methods.
		virtual void initCustomVarsLocations();
		virtual void prepareForRender();

	protected:
		// Constructor.
		Shader(const std::string& name);

		// Fields.
		std::string _vertexSrc;
		std::string _fragmentSrc;

		bool _wasCompiled;
		size_t _shadersCompileCount;

		GLuint _glVertexShader;		// Vertices rendering
		GLuint _glFragmentShader;	// Faces rendering.
		GLuint _glShaderProgram;	// Total shadering program.

	private:
		// Methods.
		bool _compileVertexShader();
		bool _compileFragmentShader();
		bool _compileShaderProgram();
};

using ShaderPtr = SharedPointer<Shader>;


#endif // __SHADER_HPP__

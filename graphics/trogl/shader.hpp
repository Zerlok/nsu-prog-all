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
		static const std::string DEFAULT_VERTEX_SRC;
		static const std::string DEFAULT_FRAGMENT_SRC;

		// Constructors / Destructor.
		Shader(const std::string& name,
			   const std::string& vertexSrc = DEFAULT_VERTEX_SRC,
			   const std::string& fragmentSrc = DEFAULT_FRAGMENT_SRC);
		Shader(const Shader& sh);
		Shader(Shader&& sh);
		virtual ~Shader();

		// Operators.
		Shader& operator=(const Shader& sh);
		Shader& operator=(Shader&& sh);

		// Methods.
		bool isCompiled() const;
		bool isValid() const;

		const GLuint& getProgram() const;

		void compile();

		// Virtual methods.
		virtual void initCustomVarsLocations(const GLuint&);
		virtual void prepareForRender();

	private:
		// Fields.
		std::string _vertexSrc;
		std::string _fragmentSrc;

		bool _isCompiled;
		size_t _shadersCompileCount;

		GLuint _glVertexShader;		// Vertices rendering
		GLuint _glFragmentShader;	// Faces rendering.
		GLuint _glShaderProgram;	// Total shadering program.

		// Methods.
		bool _compileVertexShader();
		bool _compileFragmentShader();
		bool _compileShaderProgram();
};

using ShaderPtr = SharedPointer<Shader>;


#endif // __SHADER_HPP__

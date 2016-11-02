#ifndef __DIFFUSE_SHADER_HPP__
#define __DIFFUSE_SHADER_HPP__


#include <string>
#include "object.hpp"
#include "mesh.hpp"
#include "light.hpp"
#include "shader.hpp"


class DiffuseShader : public Shader
{
	public:
		// Constructors / Destructor.
		DiffuseShader();
		~DiffuseShader();

		// Methods.
		void passMesh(Mesh const* mesh);
		void passLight(Light const* light);

		// Overriden methods.
		void initCustomVarsLocations() override;
		void passObject(const Object* obj) override;
		void prepareForRender() override;

	private:
		// Static fields.
		static const std::string VS_FILE;
		static const std::string FS_FILE;

		// Fields.
		GLuint _attrMeshPosition;
		GLuint _attrLampType;
		GLuint _attrLampPosition;
		GLuint _attrLampPower;
		GLuint _attrLampDirection;
		GLuint _attrLampColor;
		GLuint _attrLampInnerAngle;
		GLuint _attrLampOutterAngle;
};


#endif // __DIFFUSE_SHADER_HPP__

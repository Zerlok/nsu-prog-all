#ifndef __DIFFUSE_SHADER_HPP__
#define __DIFFUSE_SHADER_HPP__


#include <string>
#include "core/object.hpp"
#include "core/mesh.hpp"
#include "core/light.hpp"
#include "core/shader.hpp"


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
		void passObject(Object const* obj) override;
		void prepareForRender() override;

	private:
		// Static fields.
		static std::string VS_FILE();
		static std::string FS_FILE();

		// Fields.
		GLuint _attrMeshPosition;
		GLuint _attrLampType;
		GLuint _attrLampPosition;
		GLuint _attrLampPower;
		GLuint _attrLampDirection;
		GLuint _attrLampColor;
		GLuint _attrLampInnerAngle;
		GLuint _attrLampOutterAngle;

		GLuint _attrTestColor;
};


#endif // __DIFFUSE_SHADER_HPP__

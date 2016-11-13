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
		// Inner classes.
		struct LampAttrs
		{
			Attr type;
			Attr position;
			Attr power;
			Attr direction;
			Attr color;
			Attr innerAngle;
			Attr outterAngle;
		};

		// Static fields.
		static std::string VS_FILE();
		static std::string FS_FILE();

		// Fields.
		Attr _attrMeshPosition;
		LampAttrs _attrLamp;

		// TODO: pass material.
};


#endif // __DIFFUSE_SHADER_HPP__

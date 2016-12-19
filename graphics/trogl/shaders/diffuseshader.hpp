#ifndef __DIFFUSE_SHADER_HPP__
#define __DIFFUSE_SHADER_HPP__


#include <string>
#include "core/component.hpp"
#include "core/object.hpp"
#include "core/mesh.hpp"
#include "core/light.hpp"
#include "core/camera.hpp"
#include "core/shader.hpp"


class DiffuseShader : public Shader
{
	public:
		// Constructors / Destructor.
		DiffuseShader();
		~DiffuseShader();

		// Methods.
		void passTexture(const int idx, const Texture* texture) const;

		void passObject(const Object* obj) const;
		void passCamera(const Camera* camera) const;
		void passLight(const Light* light) const;
		void passMesh(const Mesh* mesh) const;

		// Overriden methods.
		void passComponent(const Component* comp) const override;
		void passArrayOfComponents(const ComponentsPtrs& components) const override;

	protected:
		void _registerAttributes() override;
		void _passInternalAttributes() override;

	private:
		// Static fields.
		static std::string VS_FILE();
		static std::string FS_FILE();
};


#endif // __DIFFUSE_SHADER_HPP__

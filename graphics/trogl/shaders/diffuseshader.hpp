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
		void passTexture(const Texture* texture);
		void passMesh(const Mesh* mesh);
		void passLight(const Light* light);
		void passCamera(const Camera* camera);

		// Overriden methods.
		void passComponent(const Component* comp) override;
		void passObject(const Object* obj) override;

	protected:
		void _registerAttributes() override;
		void _passInternalAttributes() override;

	private:
		// Static fields.
		static std::string VS_FILE();
		static std::string FS_FILE();
};


#endif // __DIFFUSE_SHADER_HPP__

#ifndef __DIFFUSE_SHADER_HPP__
#define __DIFFUSE_SHADER_HPP__


#include <string>
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
		void passMesh(Mesh const* mesh);
		void passLight(Light const* light);
		void passCamera(Camera const* camera);

		// Overriden methods.
		void passObject(Object const* obj) override;

	protected:
		void _registerAttributes() override;
		void _passInternalAttributes() override;

	private:
		// Static fields.
		static std::string VS_FILE();
		static std::string FS_FILE();
};


#endif // __DIFFUSE_SHADER_HPP__

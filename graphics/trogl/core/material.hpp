#ifndef __MATERIAL_HPP__
#define __MATERIAL_HPP__


#include <sharedpointer.h>
#include "common/color.hpp"
#include "texture.hpp"
#include "shader.hpp"
#include "component.hpp"


class Material : public Component
{
	public:
		// Constructors / Destructor.
		Material(const std::string& name,
				 const Color& color,
				 const ShaderPtr& shader = nullptr);
		Material(const Material& mat);
		Material(Material&& mat);
		virtual ~Material();

		// Operators.
		Material& operator=(const Material& mat);
		Material& operator=(Material&& mat);

		Material& operator+=(const Material& mat);
		Material& operator*=(const float& ratio);
		Material operator+(const Material& mat) const;
		Material operator*(const float& ratio) const;

		// Methods.
		bool isValid() const;

		const Color& getColor() const;
		const float& getTextureMixing() const;
		const Textures& getTextures() const;
		const ShaderPtr& getShader() const;

		void compile();

		void setColor(const Color& color);
		void setTextureMixing(const float& mixing);
		void addTexture(const TexturePtr& texture);

		// Virtual methods.
		virtual void use();

	protected:
		// Fields.
		Color _color;
		Textures _textures;
		float _texturesMixing;
		ShaderPtr _shader;

		void _setShader(const ShaderPtr& shader);
		void _regProperties() override;
};

using MaterialPtr = SharedPointer<Material, Component>;


#endif // __MATERIAL_HPP__

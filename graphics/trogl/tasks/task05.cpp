#include "task05.hpp"


#include "textures/imagetexture.hpp"
#include "materials/diffusematerial.hpp"
#include "meshes/sphere.hpp"


Task05NormalMappingEarth::Task05NormalMappingEarth()
	: Task("Task05 - Normal Mapping (Earth)")
{
//	engine.enableCameraRotation();
//	engine.setRenderMode(Engine::RenderMode::EDGES);

	camera->setPosition({0.0, 3.0, 10.0});

	MaterialPtr mat = new DiffuseMaterial(Color::blue, 1.0, 0.0, 50.0);
	mat->setTextureMixing(1.0);

	TexturePtr rgbTex = new ImageTexture("/home/zerlok/nsu_prog/graphics/trogl/data/earth.jpg");
	rgbTex->setColorMix(1.0);
	rgbTex->setNormal(0.0);
	rgbTex->setFiltering(Texture::Filtering::ANISOTROPIC);
	mat->addTexture(rgbTex);

	TexturePtr normalTex = new ImageTexture("/home/zerlok/nsu_prog/graphics/trogl/data/earth_normal.jpg");
	normalTex->setColorMix(0.0);
	normalTex->setNormal(1.0);
	normalTex->setFiltering(Texture::Filtering::BILINEAR);
	mat->addTexture(normalTex);

	MeshPtr earth = new Sphere(4.0, 31, 62);
	earth->setMaterial(mat);

	scene->addMesh(earth);

	addDefaultCameraRotation();
	addDefaultSunRotation();
}

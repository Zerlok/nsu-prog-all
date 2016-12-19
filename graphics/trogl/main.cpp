#include <iostream>
#include <iomanip>
#include <logger.hpp>

#include "common/utils.hpp"
#include "common/color.hpp"

#include "textures/imagetexture.hpp"
#include "textures/squaredwbtexture.hpp"

#include "shaders/diffuseshader.hpp"
#include "materials/diffusematerial.hpp"

#include "meshes/sphere.hpp"
#include "meshes/plane.hpp"

#include "engine.hpp"
#include "engineutils.hpp"


//logger_t globalLogging = loggerGlobal(loggerLDebug, loggerDFull);
logger_t globalLogger = loggerInit(std::cout, loggerLDebug, loggerDFull);


int main(int argc, char *argv[])
{
	// Some mesh generation attributes.
	const size_t size = 4;
	const float offset = 2.5;

	// Setup scene.
	CameraPtr camera = new Camera(1000, 800);
	camera->setPosition({0.0, 5.0, 15.0});

	ScenePtr scene = new Scene("My Scene", camera);
	scene->setBgColor(Color::grey);
	scene->setAmbient(0.7);

	Plane basePlane = Plane();
	basePlane.setPosition({-5.0, 0.0, -5.0});
	basePlane.setScale({2.0, 1.0, 30.0});
	const glm::vec3 direction {1.0, 0.0, 0.0};
	using MeshGenerator = ObjectGenerator<Plane, ObjectGeneratorTraits<Mesh> >;
	MeshGenerator meshGenerator;
	MeshGenerator::Objects meshes = meshGenerator.directionArrangement(size, offset, direction, basePlane);

	TexturePtr tex;
	MaterialPtr mat;
	for (size_t i = 0; i < meshes.size(); ++i)
	{
		tex = new ImageTexture("/home/zerlok/Pictures/me.jpg");
//		tex = new SquaredWBTexture(100, 100);
		tex->setColorMix(1.0);
		tex->setUVScale({1.0, 1.0/15.0});

		switch (i)
		{
			case 3:
//				tex->setFiltering(Texture::Filtering::ANISOTROPHIC);
				break;
			case 2:
				tex->setFiltering(Texture::Filtering::TRILINEAR);
				break;
			case 1:
				tex->setFiltering(Texture::Filtering::BILINEAR);
				break;
			case 0:
			default:
				tex->setFiltering(Texture::Filtering::NONE);
				break;
		}

		mat = new DiffuseMaterial(Color::white, 1.0, 0.2, 2.0);
		mat->addTexture(tex);

		meshes[i]->setMaterial(mat);
		scene->addMesh(meshes[i]);
	}

	// Add light to the scene.
//	LightPtr lamp = new Light(Light::createPoint());
	LightPtr lamp = new Light(Light::createSun());
//	LightPtr lamp = new Light(Light::createSpot());
//	LightPtr lamp = scene->getAmbientLight();
//	lamp->setColor({200, 200, 255});
	scene->addLight(lamp);

	// Show scene.
	Engine& engine = Engine::instance();
	engine.enableFPS();
	engine.setRenderMode(Engine::RenderMode::POLYGONS);
	engine.setActiveScene(scene);
	engine.showActiveScene();

	return 0;
}

#include "task04.hpp"


#include "textures/imagetexture.hpp"
#include "textures/squaredwbtexture.hpp"
#include "shaders/diffuseshader.hpp"
#include "materials/diffusematerial.hpp"
#include "meshes/plane.hpp"
#include "meshes/sphere.hpp"

#include "engineutils.hpp"


Task04TexturesFiltering::Task04TexturesFiltering()
	: Task("Task04 - Textures Filtering")
{
	// Some mesh generation attributes.
	const size_t size = 4;
	const float offset = 2.1;

	camera->setPosition({0.0, 6.0, 20.0});

	Plane basePlane = Plane();
	basePlane.setPosition({-3.0, 0.0, -1.0});
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
//		tex = new SquaredWBTexture(16, 16);
		tex->setUVScale({1.0, 1.0/20.0});

		switch (i)
		{
			case 3:
				tex->setFiltering(Texture::Filtering::ANISOTROPIC);
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
		mat->setTextureMixing(1.0);
		mat->addTexture(tex);

		meshes[i]->setMaterial(mat);
		scene->addMesh(meshes[i]);
	}

	// Add light to the scene.
	LightPtr sun = new Light(Light::createSun());
//	sun->setColor({200, 200, 255});
	scene->addLight(sun);
}


Task04TexturesMixingRoad::Task04TexturesMixingRoad()
	: Task("Task04 - Textures Mixing (Road)")
{
	camera->setPosition({0.0, 6.0, 20.0});

	TexturePtr roadTexture = new ImageTexture("/home/zerlok/nsu_prog/graphics/trogl/data");
	TexturePtr sidesTexture = new ImageTexture("/home/zerlok/nsu_prog/graphics/trogl/data");
	TexturePtr crossingsTexture = new ImageTexture("/home/zerlok/nsu_prog/graphics/trogl/data");

	MaterialPtr roadMaterial = new DiffuseMaterial(Color::grey, 1.0, 0.2);
	roadMaterial->setTextureMixing(1.0);
	roadMaterial->addTexture(roadTexture);
	roadMaterial->addTexture(sidesTexture);
	roadMaterial->addTexture(crossingsTexture);

	MeshPtr road = new Plane();
	road->setPosition({-3.0, 0.0, -1.0});
	road->setScale({4.0, 1.0, 30.0});
	road->setMaterial(roadMaterial);

	scene->addMesh(road);
}


Task04EarthSphereUVMapping::Task04EarthSphereUVMapping()
	: Task("Task04 - Sphere UV Mapping (Earth)")
{
	camera->setPosition({0.0, 6.0, 20.0});

}

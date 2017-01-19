#include "projectshadows.hpp"


#include <fstream>
#include <logger.hpp>
#include "shaders/lightshader.hpp"
#include "meshes/importexport.hpp"
#include "meshes/plane.hpp"
#include "materials/diffusematerial.hpp"


logger_t moduleLogger = loggerModule(loggerLDebug, loggerDFull);


Tester::Tester(const std::string& name)
	: Task(name),
	  _tests()
{
}


Tester::~Tester()
{
	for (Task* t : _tests)
		delete t;
}


void Tester::add(Task* test)
{
	_tests.push_back(test);
}


void Tester::run()
{
	logInfo << "Running tests." << logEndl;

	for (Task* t : _tests)
		t->run();
}


TestRTT::TestRTT()
	: Task("Shadows - render to texture test.")
{
	engine.setFrame(Engine::FrameType::RTT);

	Importer meshGen;
	std::ifstream houseFile("/home/zerlok/nsu_prog/graphics/trogl/data/house.obj");
	MeshPtr house = meshGen.parse(houseFile);
	scene->addMesh(house);
	MeshPtr house2 = new Mesh(house.get_creference());
	house2->setPosition(-5.0f, -5.0f, -5.0f);
//	scene->addMesh(house2);

	MeshPtr plane = new Plane();
//	ShaderPtr sh = new Shader("Specialsh", {Shader::pathTo("tts.vs"), Shader::pathTo("tts.fs")}, {"position", "normal", "uvMap"});
	MaterialPtr mat = new DiffuseMaterial(Color::white, 0.0, 0.0, 0.0);
	plane->setMaterial(mat);
	plane->setScale(20.0f, 1.0f, 20.0f);
	plane->setRotation(1.57f, 0.0f, 0.0f);
	plane->setPosition(-10.0f, 0.0f, -10.0f);
	scene->addMesh(plane);

	LightPtr sun = new Light(Light::createSun());
	sun->setShader(new LightShader());
	sun->setPosition(camera->getPosition());
	sun->faceDirectionTo({0.0f, 1.0f, 1.0f});
	scene->addLight(sun);
}


ShadowsTesting::ShadowsTesting()
	: Tester("Shadows testing")
{
	add(new TestRTT());

	engine.setFPSLimit(60);
}

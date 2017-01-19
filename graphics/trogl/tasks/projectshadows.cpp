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
	: Task("Shadows - render to texture test."),
	  _cameraCntrl(camera)
{
	Keyboard& kb = engine.getKeyboard();
	kb.bind(Keyboard::Key::ANY, _cameraCntrl.getKBListener());
	Mouse& m = engine.getMouse();
	m.bind(Mouse::Type::MOVE, _cameraCntrl.getMListener());

	engine.setFrame(Engine::FrameType::RTT);

	Importer meshGen;
	std::ifstream houseFile("/home/zerlok/nsu_prog/graphics/trogl/data/house.obj");
	MeshPtr house = meshGen.parse(houseFile);
	scene->addMesh(house);

	MeshPtr plane = new Plane();
	MaterialPtr mat = new DiffuseMaterial(Color::white, 1.0, 1.0, 5.0);
	plane->setMaterial(mat);
	plane->setPosition(0.0, -5.0, 0.0);
	plane->setScale(20.0f, 1.0f, 20.0f);
	scene->addMesh(plane);

	LightPtr sun = new Light(Light::createSun());
	sun->setShader(new LightShader());
	sun->setPosition({5.0f, 5.0f, 5.0f});
	sun->faceDirectionTo({0.0f, 0.0f, 0.0f});
	scene->addLight(sun);

//	addDefaultSunRotation();
}


ShadowsTesting::ShadowsTesting()
	: Tester("Shadows testing")
{
	add(new TestRTT());

	engine.setFPSLimit(60);
}

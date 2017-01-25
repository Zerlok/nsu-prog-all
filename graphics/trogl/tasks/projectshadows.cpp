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
	camera->setPosition({0.0, 3.0, 4.0});
	camera->setLookingAtPosition({0.0, 1.0, 0.0});

	Importer fileReader;
	std::ifstream cubeFile("/home/zerlok/nsu_prog/graphics/trogl/data/cube.obj");
	MeshPtr cube= fileReader.parse(cubeFile);
	MeshPtr cube2 = new Mesh(cube);
	cube->setPosition(0.2, 1.0, 0.0);
	cube->setScale(0.5, 1.0, 0.5);
	scene->addMesh(cube);

	scene->addMesh(cube2);

	std::ifstream sphereFile("/home/zerlok/nsu_prog/graphics/trogl/data/sphere.obj");
	MeshPtr sphere = fileReader.parse(sphereFile);
	sphere->setPosition(1.5, 0.25, 0.0);
	sphere->setScale(1.5, 1.5, 1.5);
	scene->addMesh(sphere);

	std::ifstream houseFile("/home/zerlok/nsu_prog/graphics/trogl/data/house.obj");
	MeshPtr house = fileReader.parse(houseFile);
	house->setPosition(1.5, 0.25, 1.5);
	house->setScale(0.2, 0.2, 0.2);
	scene->addMesh(house);

	MeshPtr plane = new Plane();
	MaterialPtr mat = new DiffuseMaterial(Color::white, 1.0, 1.0, 5.0);
	plane->setMaterial(mat);
	plane->setPosition(0.0, -0.5, 0.0);
	plane->setScale(20.0f, 1.0f, 20.0f);
	scene->addMesh(plane);

	LightPtr sun = new Light(Light::createSun());
	sun->setShader(new LightShader());
	// FIXME: no shadows when this line (setPosition) is disabled (Light::createSun function has the same line, but doesn't acts).
	sun->setPosition({0.0f, 10.0f, 0.0f});
	scene->addLight(sun);

	addDefaultSunRotation();
	AnimationPtr lampAnim = scene->getAnimations().back();
	kb.bind(Keyboard::Key::P, new AnimController(lampAnim));
}


ShadowsTesting::ShadowsTesting()
	: Tester("Shadows testing")
{
	add(new TestRTT());

	engine.setFPSLimit(60);
}


AnimController::AnimController(Animation& anim)
	: _anim(anim)
{
}


void AnimController::onKeyPressed(const Keyboard::Key& key)
{
	if (key != Keyboard::Key::P)
		return;

	if (_anim.isPaused())
		_anim.resume();
	else
		_anim.pause();
}


void AnimController::onKeyReleased(const Keyboard::Key& key)
{

}

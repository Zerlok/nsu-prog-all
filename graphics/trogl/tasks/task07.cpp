#include "task07.hpp"


#include <fstream>
#include "meshes/importexport.hpp"


Task07ActionInput::Task07ActionInput()
	: Task("Task07 - Keyboard and Mouse interaction"),
	  _cameraCntrl(new CameraController(scene->getCamera()))
{
	Keyboard& kb = engine.getKeyboard();
	kb.bind(Keyboard::Key::ARROW_UP, _cameraCntrl);
	kb.bind(Keyboard::Key::ARROW_DOWN, _cameraCntrl);
	kb.bind(Keyboard::Key::ARROW_LEFT, _cameraCntrl);
	kb.bind(Keyboard::Key::ARROW_RIGHT, _cameraCntrl);

	std::ifstream in("/home/zerlok/nsu_prog/graphics/trogl/data/house.obj");
	Importer mi;
	scene->addMesh(mi.parse(in));
	camera->setPosition({0.0f, 2.0f, 5.0f});
}


CameraController::CameraController(const CameraPtr& camera)
	: _camera(camera)
{
}


CameraController::~CameraController()
{
}


void CameraController::onKeyPressed(const Keyboard::Key& key)
{
	static const float velocity = 1.0;
	Object::vec pos;

	switch (key)
	{
		case Keyboard::Key::ARROW_UP:
			pos = Object::vec(0.0, 0.0, velocity);
			break;
		case Keyboard::Key::ARROW_DOWN:
			pos = Object::vec(0.0, 0.0, -velocity);
			break;
		case Keyboard::Key::ARROW_LEFT:
			pos = Object::vec(velocity, 0.0, 0.0);
			break;
		case Keyboard::Key::ARROW_RIGHT:
			pos = Object::vec(-velocity, 0.0, 0.0);
			break;
		default:
			return;
	}

	_camera->setPosition(_camera->getPosition() + pos);
//	std::cout << _camera->getPosition() << std::endl;
}


void CameraController::onKeyReleased(const Keyboard::Key& key)
{
}

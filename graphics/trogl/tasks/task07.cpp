#include "task07.hpp"


#include <fstream>
#include "meshes/importexport.hpp"


Task07ActionInput::Task07ActionInput()
	: Task("Task07 - Keyboard and Mouse interaction"),
	  _cameraCntrl(scene->getCamera())
{
	Keyboard& kb = engine.getKeyboard();
	kb.bind(Keyboard::Key::ARROW_UP, _cameraCntrl.getKBListener());
	kb.bind(Keyboard::Key::ARROW_DOWN, _cameraCntrl.getKBListener());
	kb.bind(Keyboard::Key::ARROW_LEFT, _cameraCntrl.getKBListener());
	kb.bind(Keyboard::Key::ARROW_RIGHT, _cameraCntrl.getKBListener());

	Mouse& m = engine.getMouse();
	m.bind(Mouse::Type::MOVE, _cameraCntrl.getMListener());
	m.bind(Mouse::Type::PRESS, _cameraCntrl.getMListener());
	m.bind(Mouse::Type::RELEASE, _cameraCntrl.getMListener());

	std::ifstream in("/home/zerlok/nsu_prog/graphics/trogl/data/house.obj");
	Importer mi;
	scene->addMesh(mi.parse(in));
	camera->setPosition({0.0f, 2.0f, 5.0f});

	addDefaultSunRotation();
}


CameraController::CameraController(const CameraPtr& camera)
	: _kb(new KBListener(camera)),
	  _m(new MListener(camera))
{
}


CameraController::KBListener* CameraController::getKBListener()
{
	return _kb;
}


CameraController::MListener* CameraController::getMListener()
{
	return _m;
}


CameraController::KBListener::KBListener(const CameraPtr& cam)
	: _camera(cam)
{
}


void CameraController::KBListener::onKeyPressed(const Keyboard::Key& key)
{
	{
		static const float velocity = 1.0;
		vec3 pos;

		switch (key)
		{
			case Keyboard::Key::ARROW_UP:
				pos = vec3(0.0, 0.0, velocity);
				break;
			case Keyboard::Key::ARROW_DOWN:
				pos = vec3(0.0, 0.0, -velocity);
				break;
			case Keyboard::Key::ARROW_LEFT:
				pos = vec3(velocity, 0.0, 0.0);
				break;
			case Keyboard::Key::ARROW_RIGHT:
				pos = vec3(-velocity, 0.0, 0.0);
				break;
			default:
				return;
		}

		_camera->setPosition(_camera->getPosition() + pos);
	//	std::cout << _camera->getPosition() << std::endl;
	}
}


void CameraController::KBListener::onKeyReleased(const Keyboard::Key& key)
{
}


CameraController::MListener::MListener(const CameraPtr& cam)
	: _camera(cam)
{
}


void CameraController::MListener::onPerformed(const Mouse::ClickEvent& click)
{
	if (click.getId() != int(Mouse::Type::MOVE))
		return;

	const float len = (_camera->getLookingAtPosition() - _camera->getPosition()).length() * 50;
	_camera->setRotation({0.0, std::asin(float(click.x) / len), 0.0});
	std::cout << _camera->getLookingAtPosition() << std::endl;
	std::cout << click.getId() << " " << int(click.getValue()) << " " << click.x << " " << click.y << std::endl;
}

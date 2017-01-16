#include "task07.hpp"


#include <fstream>
#include "meshes/importexport.hpp"


Task07ActionInput::Task07ActionInput()
	: Task("Task07 - Keyboard and Mouse interaction"),
	  _cameraCntrl(scene->getCamera())
{
	Keyboard& kb = engine.getKeyboard();
	kb.bind(Keyboard::Key::W, _cameraCntrl.getKBListener());
	kb.bind(Keyboard::Key::S, _cameraCntrl.getKBListener());
	kb.bind(Keyboard::Key::A, _cameraCntrl.getKBListener());
	kb.bind(Keyboard::Key::D, _cameraCntrl.getKBListener());

	Mouse& m = engine.getMouse();
	m.bind(Mouse::Type::MOVE, _cameraCntrl.getMListener());

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
	static const float velocity = 0.1;

	const vec3& head = _camera->getHeadDirection();
	const vec3 direction = _camera->getLookingAtPosition() - _camera->getPosition();
	const vec3 forward = glm::normalize(direction) * velocity;
	const vec3 right = glm::normalize(glm::cross(direction, head)) * velocity;
	vec3 pos = _camera->getPosition();

	switch (key)
	{
		case Keyboard::Key::W:
			pos += forward;
			break;
		case Keyboard::Key::S:
			pos -= forward;
			break;
		case Keyboard::Key::D:
			pos += right;
			break;
		case Keyboard::Key::A:
			pos -= right;
			break;
		default:
			return;
	}

	_camera->setPosition(pos);
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
	const vec3& head = _camera->getHeadDirection();
	const vec3 direction = _camera->getLookingAtPosition() - _camera->getPosition();
	const vec3 right = glm::normalize(glm::cross(direction, head));
	const vec3 up = glm::normalize(glm::cross(right, direction));
	const float len = direction.length() * 60;

	const float phy = -std::sin((click.x % 60) / len) * ((click.x / 60) + 1);
	const float thetta = -std::sin((click.y % 60) / len) * ((click.y / 60) + 1);

	const glm::mat3x3 rotX = glm::mat3x3(glm::rotate(matrix::identic::m4x4, phy, head));
	const glm::mat3x3 rotXY = glm::mat3x3(glm::rotate(matrix::identic::m4x4, thetta, right)) * rotX;

	const vec3 up1 = rotXY * up;
	if (glm::dot(up1, head) > 0.0f)
		_camera->setLookingAtPosition((rotXY * direction) + _camera->getPosition());
	else
		_camera->setLookingAtPosition((rotX * direction) + _camera->getPosition());
}

#include "task07.hpp"


#include <fstream>
#include "meshes/importexport.hpp"


Task07ActionInput::Task07ActionInput()
	: Task("Task07 - Keyboard and Mouse interaction"),
	  _cameraCntrl(scene->getCamera())
{
	Keyboard& kb = engine.getKeyboard();
	kb.bind(Keyboard::Key::ANY, _cameraCntrl.getKBListener());

	Mouse& m = engine.getMouse();
	m.bind(Mouse::Type::MOVE, _cameraCntrl.getMListener());

	std::ifstream in("/home/zerlok/nsu_prog/graphics/trogl/data/house.obj");
	Importer mi;
	scene->addMesh(mi.parse(in));

	addDefaultSunRotation();
}


CameraController::CameraController(const CameraPtr& camera)
	: _camera(camera),
	  _kb(new KBListener(*this)),
	  _m(new MListener(*this)),
	  _flyEnabled(false),
	  _velocity(0.05),
	  _sensivity(60.0)
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


void CameraController::_onKey(const Keyboard::Key& key)
{
	const vec3& head = _camera->getHeadDirection();
	const vec3 direction = _camera->getLookingAtPosition() - _camera->getPosition();
	const vec3 forward = glm::normalize(direction) * _velocity;
	const vec3 right = glm::normalize(glm::cross(direction, head)) * _velocity;
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
		case Keyboard::Key::F:
			_flyEnabled = !_flyEnabled;
		default:
			return;
	}

	if (_flyEnabled)
		_camera->setPosition(pos);
}


void CameraController::_onMouseMove(const int& x, const int& y)
{
	if (!_flyEnabled)
		return;

	const vec3& head = _camera->getHeadDirection();
	const vec3 direction = _camera->getLookingAtPosition() - _camera->getPosition();
	const vec3 right = glm::normalize(glm::cross(direction, head));
	const vec3 up = glm::normalize(glm::cross(right, direction));
	const float len = direction.length() * _sensivity;

	const float phy = -std::sin((x % 60) / len) * ((x / 60) + 1);
	const float thetta = -std::sin((y % 60) / len) * ((y / 60) + 1);

	const glm::mat3x3 rotX = glm::mat3x3(glm::rotate(matrix::identic::m4x4, phy, head));
	const glm::mat3x3 rotXY = glm::mat3x3(glm::rotate(matrix::identic::m4x4, thetta, right)) * rotX;

	const vec3 up1 = rotXY * up;
	if (glm::dot(up1, head) > 0.0f)
		_camera->setLookingAtPosition((rotXY * direction) + _camera->getPosition());
	else
		_camera->setLookingAtPosition((rotX * direction) + _camera->getPosition());
}


CameraController::KBListener::KBListener(CameraController& cntrl)
	: _cntrl(cntrl)
{
}


void CameraController::KBListener::onKeyPressed(const Keyboard::Key& key)
{
	_cntrl._onKey(key);
}


void CameraController::KBListener::onKeyReleased(const Keyboard::Key& key)
{
}


CameraController::MListener::MListener(CameraController& cntrl)
	: _cntrl(cntrl)
{
}


void CameraController::MListener::onPerformed(const Mouse::ClickEvent& click)
{
	_cntrl._onMouseMove(click.x, click.y);
}

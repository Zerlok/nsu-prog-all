#include "peripherals.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLInfo, loggerDFull);


// ------------------------------ KEYBOARD ------------------------------ //


const Keyboard::KeyEvent Keyboard::KEY_PRESSED(1, Keyboard::Key::ANY);
const Keyboard::KeyEvent Keyboard::KEY_RELEASED(2, Keyboard::Key::ANY);


Keyboard& Keyboard::instance()
{
	static Keyboard kb;
	return kb;
}


Keyboard::Handler& Keyboard::getHandler()
{
	return _handler;
}


void Keyboard::bind(const Keyboard::Key& key, Keyboard::KeyListener* listener)
{
	_handler.registrate(KeyEvent(KEY_PRESSED.getId(), key), listener);
	_handler.registrate(KeyEvent(KEY_RELEASED.getId(), key), listener);
}


void Keyboard::setKeyPressed(const int& code)
{
	Code2KeyMap::const_iterator it = _codeTable.find(code);
	if (it == _codeTable.cend())
	{
		logDebug << "Keyboard code: '" << code << "' was not found in code2key translation table." << logEndl;
		return;
	}

	const Key& key = (*it).second;
	_handler.push(KeyEvent(KEY_PRESSED.getId(), key));
	logDebug << "Keyboard: " << int(key) << " key pressed." << logEndl;
}


void Keyboard::setKeyReleased(const int& code)
{
	Code2KeyMap::const_iterator it = _codeTable.find(code);
	if (it == _codeTable.cend())
	{
		logDebug << "Keyboard code: '" << code << "' was not found in code2key translation table." << logEndl;
		return;
	}

	const Key& key = (*it).second;
	_handler.push(KeyEvent(KEY_RELEASED.getId(), key));
	logDebug << "Keyboard: " << int(key) << " key released." << logEndl;
}


void Keyboard::setTranslationTable(const Code2KeyMap& table)
{
	_codeTable = table;
}


void Keyboard::setTranslationTable(Code2KeyMap&& table)
{
	_codeTable = table;
}


Keyboard::Keyboard()
{
}


Keyboard::~Keyboard()
{
}


Keyboard::KeyListener::KeyListener()
	: EventListener<KeyEvent>()
{
}


Keyboard::KeyListener::~KeyListener()
{
}


void Keyboard::KeyListener::onPerformed(const Keyboard::KeyEvent& kbEvent)
{
	if (kbEvent == KEY_PRESSED)
		onKeyPressed(kbEvent.getValue());
	else if (kbEvent == KEY_RELEASED)
		onKeyReleased(kbEvent.getValue());
}


// ------------------------------ MOUSE ------------------------------ //


Mouse::ClickEvent::ClickEvent(const Mouse::Type& type,
							  const Mouse::Button& btn,
							  const int& x,
							  const int& y)
	: Event(int(type), btn), x(x), y(y)
{
}


Mouse& Mouse::instance()
{
	static Mouse m;
	return m;
}


void Mouse::bind(const Mouse::Type& type, Mouse::Listener* listener)
{
	_handler.registrate(ClickEvent(type, Button::NONE, 0, 0), listener);
}


int Mouse::getX() const
{
	return _x;
}


int Mouse::getY() const
{
	return _y;
}


void Mouse::setPos(const int& x, const int& y)
{
	_x = x;
	_y = y;
}


void Mouse::moveTo(const int& x, const int& y)
{
	_handler.push(ClickEvent(Type::MOVE, _activeBtn, (x - _x), (y - _y)));

	_x = x;
	_y = y;
}


void Mouse::reset(const int& button,
				  const int& state,
				  const int& x,
				  const int& y)
{
	switch (button)
	{
		case 0:
			_activeBtn = Button::LEFT;
			break;
		case 1:
			_activeBtn = Button::MIDDLE;
			break;
		case 2:
			_activeBtn = Button::RIGHT;
			break;
		case 3:
			_activeBtn = Button::SCROLL_UP;
			break;
		case 4:
			_activeBtn = Button::SCROLL_DOWN;
			break;
	}

	Type st;
	switch (state)
	{
		case 0:
			st = Type::PRESS;
			break;
		case 1:
			st = Type::RELEASE;
			break;
	}

	_handler.push(ClickEvent(st, _activeBtn, x, y));

	if (st == Type::RELEASE)
		_activeBtn = Button::NONE;
}


Mouse::Handler& Mouse::getHandler()
{
	return _handler;
}


Mouse::Mouse()
	: _activeBtn(Button::NONE),
	  _x(0), _y(0),
	  _handler()
{
}


Mouse::~Mouse()
{
}

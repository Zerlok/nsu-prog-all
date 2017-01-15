#include "peripherals.hpp"


#include <logger.hpp>


logger_t moduleLogger = loggerModule(loggerLInfo, loggerDFull);


// ------------------------------ KEYBOARD ------------------------------ //


const Keyboard::KeyEvent Keyboard::KEY_PRESSED(1, Keyboard::Key::ANY);
const Keyboard::KeyEvent Keyboard::KEY_RELEASED(2, Keyboard::Key::ANY);


Keyboard&Keyboard::instance()
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

Mouse& Mouse::instance()
{
	static Mouse m;
	return m;
}


Mouse::Handler& Mouse::getHandler()
{
	return _handler;
}


Mouse::Mouse()
{
}


Mouse::~Mouse()
{
}

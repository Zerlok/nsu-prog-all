#ifndef __PERIPHERALS_HPP__
#define __PERIPHERALS_HPP__


#include <vector>
#include <unordered_map>
#include "event.hpp"


class Keyboard
{
	public:
		enum class Key : int
		{
			ANY = 0,
			A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
			RETURN, BACKSPACE, SPACE, ESCAPE, TAB,
			ARROW_UP, ARROW_DOWN, ARROW_RIGHT, ARROW_LEFT,
			SHIFT_RIGHT, SHIFT_LEFT,
			CTRL_RIGHT, CTRL_LEFT,
			ALT_RIGHT, ALT_LEFT,
		};

		using KeyEvent = Event<Key>;
		static const KeyEvent KEY_PRESSED;
		static const KeyEvent KEY_RELEASED;

		class KeyListener : public EventListener<KeyEvent>
		{
			public:
				KeyListener();
				virtual ~KeyListener();

				void onPerformed(const KeyEvent& kbEvent) override;

				virtual void onKeyPressed(const Keyboard::Key& code) = 0;
				virtual void onKeyReleased(const Keyboard::Key& code) = 0;
		};
		using Handler = EventsHandler<KeyEvent, KeyListener>;
		using Code2KeyMap = std::unordered_map<int, Key>;

		static Keyboard& instance();

		Handler& getHandler();

		void bind(const Key& key, KeyListener* listener);

		void setKeyPressed(const int& code);
		void setKeyReleased(const int& code);

		void setTranslationTable(const Code2KeyMap& c2kMap);
		void setTranslationTable(Code2KeyMap&& c2kMap);

	private:
		Handler _handler;
		Code2KeyMap _codeTable;

		Keyboard();
		~Keyboard();
};


class Mouse
{
	public:
		enum class Code
		{
			NONE = 0,
			LEFT = 1,
			RIGHT = 2,
			MIDDLE = 3,
//			SCROLL_UP,
//			SCROLL_DOWN,
		};

		static Mouse& instance();

		int getX() const;
		int getY() const;
		const Code& getState() const;

		void reset(const int& x, const int& y, const Code& code);

	private:
		int _x;
		int _y;
		Code _code;

		Mouse();
		~Mouse();
};


#endif // __PERIPHERALS_HPP__

#ifndef __DECORATORS_H__
#define __DECORATORS_H__


#include <iostream>
#include <string>
#include <sstream>
#include <vector>


class Component
{
	public:
		Component();
		Component(std::istream& in);
		~Component() {}

		std::string get_line();
		void reset_line(const std::string& line);

		friend std::istream& operator>>(std::istream&, Component&);
		friend std::ostream& operator<<(std::ostream&, Component&);

	protected:
		std::stringstream _text_stream;

	private:
		std::stringstream::pos_type _input_pos;
		std::stringstream::pos_type _output_pos;
};


std::istream& operator>>(std::istream&, Component&);
std::ostream& operator<<(std::ostream&, Component&);


class HTMLComponent : public Component
{
	public:
		HTMLComponent();
		HTMLComponent(const HTMLComponent&);
		~HTMLComponent();
};


class Decorator
{
	public:
		Decorator()
			: _inner(nullptr) {}
		Decorator(Decorator* inner)
			: _inner(inner) {}
		virtual ~Decorator();

		void wrap(Decorator& inner);
		virtual void execute(std::istream& in, std::ostream& out);

	protected:
		Decorator* _inner;
};


class HTMLDecorator : public Decorator
{
	public:
		HTMLDecorator() {}
		HTMLDecorator(Decorator* inner)
			: Decorator(inner) {}
		~HTMLDecorator() {}

		void execute(std::istream& in, std::ostream& out) override;
};


class LineNumbersDecorator : public Decorator
{
	public:
		LineNumbersDecorator() {}
		LineNumbersDecorator(Decorator* inner)
			: Decorator(inner) {}
		~LineNumbersDecorator() {}

		void execute(std::istream& in, std::ostream& out) override;
};


class KeywordsHighlightDecorator : public Decorator
{
	public:
		using WordsSet = std::vector<std::string>;

		KeywordsHighlightDecorator() {}
		KeywordsHighlightDecorator(Decorator* inner)
			: Decorator(inner) {}
		~KeywordsHighlightDecorator() {}

		size_t highlight(std::string& data,
					   const std::string& word,
					   const std::string& left_tag,
					   const std::string& right_tag = "");
		void execute(std::istream& in, std::ostream& out) override;

	private:
		static const WordsSet _macroses;
		static const WordsSet _basetypes;
		static const WordsSet _basewords;
};


class StringHighlightDecorator : public Decorator
{
	public:
		StringHighlightDecorator() {}
		StringHighlightDecorator(Decorator* inner)
			: Decorator(inner) {}
		~StringHighlightDecorator() {}

		void execute(std::istream& in, std::ostream& out) override;
};


// __DECORATORS_H__
#endif

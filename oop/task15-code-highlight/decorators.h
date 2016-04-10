#ifndef __DECORATORS_H__
#define __DECORATORS_H__


#include <iostream>
#include <unordered_set>


class Decorator
{
	public:
		Decorator()
			: _inner(nullptr) {}
		Decorator(Decorator* inner)
			: _inner(inner) {}
		virtual ~Decorator();

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
		using WordsSet = std::unordered_set<std::string>;

		KeywordsHighlightDecorator() {}
		KeywordsHighlightDecorator(Decorator* inner)
			: Decorator(inner) {}
		~KeywordsHighlightDecorator() {}

		void execute(std::istream& in, std::ostream& out) override;

	private:
		static const WordsSet _basetypes;
		static const WordsSet _basewords;
};


// __DECORATORS_H__
#endif

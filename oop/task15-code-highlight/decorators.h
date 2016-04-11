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

		void search_replace(std::string& data, const std::string& sub, const std::string& repl);
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

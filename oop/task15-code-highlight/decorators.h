#ifndef __DECORATORS_H__
#define __DECORATORS_H__


#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "component.h"


namespace htmltags
{
	static const std::string doctype = "<!DOCTYPE html>";

	static const std::string b_html = "<html>";
	static const std::string b_body = "<body>";
	static const std::string b_head = "<head>";
	static const std::string b_style = "<style>";
	static const std::string b_code = "<pre>";

	static const std::string e_html = "</html>";
	static const std::string e_body = "</body>";
	static const std::string e_head = "</head>";
	static const std::string e_style = "</style>";
	static const std::string e_code = "</pre>";
}

namespace symbols
{
	namespace code
	{
		static const std::string comment = "//";
		static const std::string quot = "\"";
		static const std::string lt = "<";
		static const std::string gt = ">";
	}

	namespace html
	{
		static const std::string quot = "&quot;";
		static const std::string lt = "&lt;";
		static const std::string gt = "&gt;";
	}
}


class HTMLComponent : public StreamComponent
{
	public:
		HTMLComponent() {}
		HTMLComponent(std::istream& in);
		~HTMLComponent() {}

		void add_style(const std::string& style);

		friend std::ostream& operator<<(std::ostream& out, const HTMLComponent& component);

	private:
		std::stringstream _styles;
};
std::ostream& operator<<(std::ostream& out, const HTMLComponent& component);


class HTMLDecorator
{
	public:
		HTMLDecorator()
			: _inner(nullptr) {}
		HTMLDecorator(HTMLDecorator& inner)
			: _inner(&inner) {}
		virtual ~HTMLDecorator() {}

		void wrap(HTMLDecorator& inner)
		{
			_inner = &inner;
		}

		virtual void execute(HTMLComponent& component)
		{
			if (_inner != nullptr)
				_inner->execute(component);
		}

		HTMLDecorator& operator<<(HTMLDecorator& inner);

	protected:
		HTMLDecorator* _inner;
};


class CodeToHTMLDecorator : public HTMLDecorator
{
	public:
		CodeToHTMLDecorator() {}
		CodeToHTMLDecorator(HTMLDecorator& inner)
			: HTMLDecorator(inner) {}
		~CodeToHTMLDecorator() {}

		void execute(HTMLComponent& component) override;
};


class LineNumbersDecorator : public HTMLDecorator
{
	public:
		LineNumbersDecorator() {}
		LineNumbersDecorator(HTMLDecorator& inner)
			: HTMLDecorator(inner) {}
		~LineNumbersDecorator() {}

		void execute(HTMLComponent& component) override;
};


class KeywordsHighlightDecorator : public HTMLDecorator
{
	public:
		using WordsSet = std::vector<std::string>;

		KeywordsHighlightDecorator() {}
		KeywordsHighlightDecorator(HTMLDecorator& inner)
			: HTMLDecorator(inner) {}
		~KeywordsHighlightDecorator() {}

		size_t highlight(std::string& data,
					   const std::string& word,
					   const std::string& left_tag,
					   const std::string& right_tag = "");
		void execute(HTMLComponent& component) override;

	private:
		static const WordsSet _macroses;
		static const WordsSet _basetypes;
		static const WordsSet _basewords;
};


class StringHighlightDecorator : public HTMLDecorator
{
	public:
		StringHighlightDecorator() {}
		StringHighlightDecorator(HTMLDecorator& inner)
			: HTMLDecorator(inner) {}
		~StringHighlightDecorator() {}

		void execute(HTMLComponent&) override;
};


// __DECORATORS_H__
#endif

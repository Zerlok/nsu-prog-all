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
		static const std::string quot = "\&quot;";
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

		virtual void add_style(HTMLComponent& component)
		{
			if (_inner != nullptr)
				_inner->add_style(component);
		}
		virtual void execute(std::string& line)
		{
			if (_inner != nullptr)
				_inner->execute(line);
		}
		virtual void execute(Component& component)
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

		void execute(std::string& line) override;
		void execute(Component& component) override;
};


class LineNumbersDecorator : public HTMLDecorator
{
	public:
		LineNumbersDecorator()
			: _line_num(1) {}
		LineNumbersDecorator(HTMLDecorator& inner)
			: HTMLDecorator(inner) {}
		~LineNumbersDecorator() {}

		const size_t& get_line_num() const;
		void reset_line_num();

		void add_style(HTMLComponent& component) override;
//		void execute(std::string& line);
		void execute(Component& component) override;

	private:
		size_t _line_num;
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

		void add_style(HTMLComponent& component) override;
		void execute(std::string& line) override;
		void execute(Component& component) override;

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

		void add_style(HTMLComponent& component) override;
		void execute(std::string& line) override;
		void execute(Component& component) override;
};


class CommentHighlightDecorator : public HTMLDecorator
{
	public:
		CommentHighlightDecorator() {}
		CommentHighlightDecorator(HTMLDecorator& inner)
			: HTMLDecorator(inner) {}
		~CommentHighlightDecorator() {}

		void add_style(HTMLComponent& component) override;
		void execute(std::string& line) override;
		void execute(Component& component) override;
};


// __DECORATORS_H__
#endif

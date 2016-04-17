#ifndef __COMPONENT_H__
#define __COMPONENT_H__


#include <iostream>
#include <string>
#include <sstream>
#include <vector>


class Component
{
	public:
		Component(const bool& clear = true,
				  const bool& ended = true)
			: _is_clear(clear),
			  _is_ended(ended) {}
		virtual ~Component() {}

		bool is_clear() const { return _is_clear; }
		bool is_ended() const { return _is_ended; }

		virtual std::string& get_string() = 0;
		virtual bool update() = 0;

	protected:
		bool _is_clear;
		bool _is_ended;
};


class StringComponent : public Component
{
	public:
		StringComponent(const std::string& s = "");
		StringComponent(const StringComponent& sc);
		StringComponent(StringComponent&& sc);
		virtual ~StringComponent() {}

		StringComponent& operator=(const StringComponent& sc);
		StringComponent& operator=(StringComponent&& sc);

		virtual std::string& get_string() override;
		virtual bool update() override;

		friend std::istream& operator>>(std::istream&, StringComponent&);
		friend std::ostream& operator<<(std::ostream&, const StringComponent&);

	protected:
		std::string _data;
};
std::istream& operator>>(std::istream&, StringComponent&);
std::ostream& operator<<(std::ostream&, const StringComponent&);


class StreamComponent : public Component
{
	public:
		typedef std::basic_ostream<char, std::char_traits<char> > std_cout_t;	// std::cout
		typedef std_cout_t& (*std_endl)(std_cout_t&);							// std::endl signature.

		StreamComponent() = default;
		StreamComponent(std::istream& in);
		StreamComponent(const StreamComponent& sc);
		StreamComponent(StreamComponent&& sc);
		virtual ~StreamComponent() {}

		StreamComponent& operator=(const StreamComponent& sc);
		StreamComponent& operator=(StreamComponent&& sc);

		virtual std::string& get_string() override;
		virtual bool update() override;

		StreamComponent& operator<<(const std::string& s);
		StreamComponent& operator<<(std_endl manipulator);

		friend std::istream& operator>>(std::istream&, StreamComponent&);
		friend std::ostream& operator<<(std::ostream&, const StreamComponent&);

	protected:
		mutable std::stringstream _stream;

	private:
		std::stringstream _buffer;
		std::string _last_string;
		std::string _next_string;
};
std::istream& operator>>(std::istream&, StreamComponent&);
std::ostream& operator<<(std::ostream&, const StreamComponent&);


class LinearComponent : public Component
{
	public:
		using Lines = std::vector<std::string>;

		LinearComponent() = default;
		LinearComponent(std::istream& in);
		LinearComponent(const LinearComponent& lc) = default;
		LinearComponent(LinearComponent&& lc) = default;
		virtual ~LinearComponent() {}

		LinearComponent& operator=(const LinearComponent& lc) = default;
		LinearComponent& operator=(LinearComponent&& lc) = default;

		virtual std::string& get_string() override;
		virtual bool update() override;

		friend std::istream& operator>>(std::istream&, LinearComponent&);
		friend std::ostream& operator<<(std::ostream&, const LinearComponent&);

	protected:
		Lines _lines;

	private:
		size_t _idx;
};
std::istream& operator>>(std::istream&, LinearComponent&);
std::ostream& operator<<(std::ostream&, const LinearComponent&);


// __COMPONENT_H__
#endif

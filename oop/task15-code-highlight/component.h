#ifndef __COMPONENT_H__
#define __COMPONENT_H__


#include <iostream>
#include <string>
#include <sstream>
#include <vector>


class Component
{
	public:
		typedef Component& (*manipulator_func_ptr)(Component&);

		static Component& endl(Component& c);

		Component(const bool& clear = true,
				  const bool& ended = true)
			: _is_clear(clear),
			  _is_ended(ended) {}
		virtual ~Component() {}

		bool is_clear() const { return _is_clear; }
		bool is_ended() const { return _is_ended; }

		virtual std::string get_string() = 0;
		virtual void push_string(const std::string& s) = 0;
		virtual bool update() = 0;

		template<class T>
		Component& operator<<(const T& val)
		{
			std::stringstream ss;
			ss << val;
			push_string(ss.str());
			return (*this);
		}

		Component& operator<<(const bool& b);
		Component& operator<<(const std::string& s);
		Component& operator<<(manipulator_func_ptr manipulator);

		Component& operator>>(std::string& s);

	protected:
		virtual void _push_line_end() = 0;

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

		std::string get_string() override;
		void push_string(const std::string& s) override;
		bool update() override;

		friend std::istream& operator>>(std::istream&, StringComponent&);
		friend std::ostream& operator<<(std::ostream&, const StringComponent&);

	protected:
		std::string _data;

	private:
		void _push_line_end() override;
		std::stringstream _buffer;
};
std::istream& operator>>(std::istream&, StringComponent&);
std::ostream& operator<<(std::ostream&, const StringComponent&);


class StreamComponent : public Component
{
	public:
		StreamComponent() = default;
		StreamComponent(std::istream& in);
		StreamComponent(const StreamComponent& sc);
		StreamComponent(StreamComponent&& sc);
		virtual ~StreamComponent() {}

		StreamComponent& operator=(const StreamComponent& sc);
		StreamComponent& operator=(StreamComponent&& sc);

		std::string get_string() override;
		void push_string(const std::string& s) override;
		bool update() override;

		friend std::istream& operator>>(std::istream&, StreamComponent&);
		friend std::ostream& operator<<(std::ostream&, const StreamComponent&);

	protected:
		mutable std::stringstream _stream;

	private:
		void _push_line_end() override;
		std::stringstream _buffer;
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

		std::string get_string() override;
		void push_string(const std::string& s) override;
		bool update() override;

		friend std::istream& operator>>(std::istream&, LinearComponent&);
		friend std::ostream& operator<<(std::ostream&, const LinearComponent&);

	protected:
		Lines _lines;

	private:
		void _push_line_end() override;
		size_t _idx;
};
std::istream& operator>>(std::istream&, LinearComponent&);
std::ostream& operator<<(std::ostream&, const LinearComponent&);


// __COMPONENT_H__
#endif

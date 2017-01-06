#ifndef __UTILS_HPP__
#define __UTILS_HPP__


#include <stddef.h>
#include <iostream>
#include <string>
#include <vector>


double getTimeDouble();
size_t getTimestamp();


namespace path
{
	std::string basename(const std::string& path);
	std::string extension(const std::string& path);
	std::string clearname(const std::string& path);
	std::string dirname(const std::string& path);
	std::string join(const std::string& path1, const std::string& path2);
}


namespace stringutils
{
	bool startswith(const std::string& str, const std::string& substr);
	bool contains(const std::string& str, const std::string& substr);

	size_t find(const std::string& str, const std::string& substr);

	template<class T>
	struct TypeTraits
	{
		T parse(const std::string& val)
		{
			return val;
		}
	};

	template<class T = std::string, class Traits = TypeTraits<T>>
	std::vector<T> split(const std::string& data,
						 const char& separator,
						 const bool& skipEmptyValues = false)
	{
		Traits typeFormat;
		std::vector<T> splitted;

		if (data.empty())
			return std::move(splitted);

		std::string str = data + separator;
		const size_t maxLength = str.length();
		std::string value;

		size_t separatorPos;
		while (!str.empty())
		{
			separatorPos = str.find(separator);
			if (separatorPos == std::string::npos)
				separatorPos = str.length();

			value = str.substr(0, separatorPos);

			if (!value.empty()
					|| !skipEmptyValues)
				splitted.push_back(typeFormat.parse(value));

			str = str.substr(separatorPos+1, maxLength);
		}

		return std::move(splitted);
	}
}


namespace vectorutils
{
	template<class T>
	T& getOrFill(std::vector<T>& values, const size_t& idx, const T& val = T())
	{
		if (idx >= values.size())
			values.resize(idx+1, val);

		return values[idx];
	}
}


template<class T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& values)
{
	out << '{';

	for (const T& val : values)
		out << val << ", ";

	out << '}';
	return out;
}


#endif // __UTILS_HPP__

#ifndef __SERIALIZER_DESERIALIZER_H__
#define __SERIALIZER_DESERIALIZER_H__


#include <iostream>
#include <iterator>
#include <vector>
#include <string>


template<class Type>
class Serializer
{
	public:
		static void Apply(std::ostream& out, const Type& obj)
		{
			const uint8_t *ptr = reinterpret_cast<const uint8_t *>(&obj);
			std::ostream_iterator<uint8_t> out_iter(out);
			std::copy(ptr, ptr + sizeof(Type), out_iter);
		}
};


template<>
class Serializer<std::string>
{
	public:
		static void Apply(std::ostream &out, const std::string &str)
		{
			Serializer<size_t>::Apply(out, str.size());
			for (const char& ch : str)
				Serializer<char>::Apply(out, ch);
		}
};


template<class Type>
class Serializer<std::vector<Type> >
{
	public:
		static void Apply(std::ostream &out, const std::vector<Type> &objs)
		{
			Serializer<size_t>::Apply(out, objs.size());
			for (const Type& obj : objs)
				Serializer<Type>::Apply(out, obj);
		}
};


template<class Type>
class Deserializer
{
	public:
		static Type& Apply(std::istream& in, Type& val)
		{
			uint8_t *ptr = reinterpret_cast<uint8_t*>(&val);
			std::istream_iterator<uint8_t> input_iter(in);
			std::copy_n(input_iter, sizeof(Type), ptr);

			return val;
		}
};


template<>
class Deserializer<std::string>
{
	public:
		static std::string& Apply(std::istream &in, std::string& val)
		{
			size_t size;
			char ch;

			Deserializer<size_t>::Apply(in, size);
			for (size_t i = 0; i < size; ++i)
				val += ch;

			return val;
		}
};


template<class Type>
class Deserializer<std::vector<Type> >
{
	public:
		static std::vector<Type>& Apply(std::istream &in, std::vector<Type> &val)
		{
			size_t size;
			Type tmp;

			Deserializer<size_t>::Apply(in, size);
			for (size_t i = 0; i < size; ++i)
			{
				Deserializer<Type>::Apply(in, tmp);
				val.push_back(tmp);
			}

			return val;
		}
};


// Base Functions.


template<class Type>
void serialize(std::ostream& out, const Type& obj)
{
	Serializer<Type>::Apply(out, obj);
}


template<class Type>
void deserialize(std::istream& in, Type& obj)
{
	in >> std::noskipws;
	Deserializer<Type>::Apply(in, obj);
	in >> std::skipws;
}


// __SERIALIZER_DESERIALIZER_H__
#endif


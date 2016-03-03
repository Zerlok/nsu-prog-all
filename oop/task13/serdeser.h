#ifndef __SERIALIZER_DESERIALIZER_H__
#define __SERIALIZER_DESERIALIZER_H__


#include <iostream>
#include <iterator>
#include <vector>
#include <list>


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


// Base Functions.


template<class Type>
void serialize(std::ostream& out, const Type& obj)
{
	Serializer<Type>::Apply(out, obj);
}


template<class Type>
void deserialize(std::istream& in, Type& obj)
{
	Deserializer<Type>::Apply(in, obj);
}


// Vector.

template<class std::vector<Type> >
void serialize(std::ostream &out, const std::vector<Type> &objs)
{
	for (const Type& obj : objs)
		Serializer<Type>::Apply(in. obj);
}


template<class std::vector<Type> >
void deserialize(std::istream& in, std::vector<Type>& obj)
{
	std::copy();
	Deserializer<Type>::Apply(in, obj);
}


template<class std::list<Type> >
void serialize(std::ostream &out, const std::list<Type> &objs)
{
	for (const Type& obj : objs)
		Serializer<Type>::Apply(in. obj);
}


// __SERIALIZER_DESERIALIZER_H__
#endif


#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__


#include <stdarg.h>
#include <array>


template<class Type>
class PoolTriats
{
	typedef void constructor_args;
};


template<class Type, int Num>
class Pool
{
	public:
		typedef Type Cls;
		typedef std::pair<Cls, bool> ObjPair;
		typedef std::array<ObjPair, Num> ObjArray;
		typedef typename PoolTriats<Cls>::constructor_args first_arg_t;

		// Constructors / Destructor.
		Pool();
		Pool(const Pool&) = delete;
		Pool(Pool&&) = delete;
		~Pool();

		// Operators.
		Pool& operator=(const Pool&) = delete;
		Pool& operator=(Pool&&) = delete;

		// Methods.
		Cls& allocate(first_arg_t arg0, ...);
		void free(Cls& instance);

	private:
		ObjArray _objects;
};


template<class T, int N>
Pool<T, N>::Pool()
	: _objects(N, {Cls(), false})
{
}


template<class T, int N>
Pool<T, N>::~Pool()
{
}


template<class T, int N>
typename Pool<T, N>::Cls& Pool<T, N>::allocate(Pool<T, N>::first_arg_t arg0, ...)
{
	for (ObjPair& pair : _objects)
	{
		if (pair.second == false) // object is not allocated.
		{
			pair.second = true;

			va_list args;
			va_start(args, arg0);
			pair.first = Cls(args);
			va_end(args);
			return pair.first;
		}
	}

	// TODO: throw exception (no free objects in pool).
	throw 1;
}


template<class T, int N>
void Pool<T, N>::free(Pool<T, N>::Cls& instance)
{
	for (ObjPair& pair : _objects)
	{
		if ((&(pair.first) == &instance)
				&& pair.second)
		{
			pair.first = Cls();
			return;
		}
	}

	// TODO: throw exception (objects is not from pool).
	throw 1;
}


// __OBJECT_POOL_H__
#endif

#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__


#include <initializer_list>
#include <exception>
#include <memory>
#include <array>


class IsNotPoolInstanceException;
class PoolOverflowException;


template<class Type, size_t Num>
class Pool
{
	public:
		// Typedefs.
		typedef std::allocator<Type> ObjAllocator;
		typedef typename ObjAllocator::pointer ObjPointer;
		typedef typename ObjAllocator::reference ObjReference;
		typedef std::pair<ObjPointer, bool> ObjPair; // pointer, is constructed.
		typedef std::array<ObjPair, Num> ObjArray;

		// Constructors / Destructor.
		Pool();
		Pool(const Pool& pool) = delete;
		Pool(Pool&& pool) = delete;
		~Pool();

		// Operators.
		Pool& operator=(const Pool&) = delete;
		Pool& operator=(Pool&&) = delete;

		// Methods.
		template<class ... Args>
		ObjReference create(Args&&... args)
		{
			for (ObjPair& pair : _objects)
			{
				if (pair.second == false) // object is not constructed.
				{
					pair.second = true;
					_object_allocator.construct(pair.first, std::forward<Args>(args)...);
					return *(pair.first);
				}
			}

			throw PoolOverflowException();
		}

		template<class InitType>
		ObjReference create(const std::initializer_list<InitType> &lst)
		{
			for (ObjPair& pair : _objects)
			{
				if (pair.second == false) // object is not constructed.
				{
					pair.second = true;
					_object_allocator.construct(pair.first, lst);
					return *(pair.first);
				}
			}

			throw PoolOverflowException();
		}

		ObjReference create(const ObjReference obj);

		void clear(ObjReference instance);

	private:
		ObjAllocator _object_allocator;
		typename ObjAllocator::pointer _objects_front;
		ObjArray _objects;
};


template<class T, size_t N>
Pool<T, N>::Pool()
{
	_objects_front = _object_allocator.allocate(N);

	for (size_t i = 0;
		 i < N;
		 ++i)
	{
		_objects[i].second = false;
		_objects[i].first = _objects_front + i;
	}
}


template<class T, size_t N>
Pool<T, N>::~Pool()
{
	for (ObjPair& pair : _objects)
	{
		if (pair.second)
		{
			pair.second = false;
			_object_allocator.destroy(pair.first);
		}
	}

	_object_allocator.deallocate(_objects_front, N);
}


template<class T, size_t N>
typename Pool<T, N>::ObjReference Pool<T, N>::create(const Pool<T, N>::ObjReference obj)
{
	for (ObjPair& pair : _objects)
	{
		if (pair.second == false) // object is not constructed.
		{
			pair.second = true;
			_object_allocator.construct(pair.first, obj);
			return *(pair.first);
		}
	}

	throw PoolOverflowException();
}


template<class T, size_t N>
void Pool<T, N>::clear(Pool<T, N>::ObjReference instance)
{
	for (ObjPair& pair : _objects)
	{
		if ((pair.first == &instance)
				&& pair.second)
		{
			pair.second = false;
			_object_allocator.destroy(pair.first);
			return;
		}
	}

	throw IsNotPoolInstanceException();
}


class IsNotPoolInstanceException : public std::exception
{
	public:
		IsNotPoolInstanceException() = default;
		~IsNotPoolInstanceException() = default;

		const char* what() const noexcept override
		{
			static const std::string msg = "Given object is not an instance from objects pool!";
			return msg.c_str();
		}
};


class PoolOverflowException : public std::exception
{
	public:
		PoolOverflowException() = default;
		~PoolOverflowException() = default;

		const char* what() const noexcept override
		{
			static const std::string msg = "Object pool overflow!";
			return msg.c_str();
		}
};


// __OBJECT_POOL_H__
#endif

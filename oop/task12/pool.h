#ifndef __OBJECT_POOL_H__
#define __OBJECT_POOL_H__


#include <memory>
#include <array>


template<class Type, int Num>
class Pool
{
	public:
		typedef Type Cls;
		typedef std::allocator<Cls> ObjAllocator;
		typedef std::pair<typename ObjAllocator::pointer, bool> ObjPair;
		typedef std::array<ObjPair, Num> ObjArray;

		// Constructors / Destructor.
		Pool();
		Pool(const Pool&) = delete;
		Pool(Pool&&) = delete;
		~Pool();

		// Operators.
		Pool& operator=(const Pool&) = delete;
		Pool& operator=(Pool&&) = delete;

		// Methods.
		template<class ... Args>
		Cls& create(Args&&... args)
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

			// TODO: throw exception (no free objects in pool).
			throw 1;
		}

		void clear(Cls& instance);
		void clear();

	private:
		typename ObjAllocator::pointer _objects_front;
		ObjAllocator _object_allocator;
		ObjArray _objects;
};


template<class T, int N>
Pool<T, N>::Pool()
{
	_objects_front = _object_allocator.allocate(N);

	if (_objects_front == nullptr)
		throw 2;

	for (size_t i = 0;
		 i < _objects.max_size();
		 ++i)
	{
		_objects[i].second = false;
		_objects[i].first = _objects_front + i;
	}
}


template<class T, int N>
Pool<T, N>::~Pool()
{
	clear();
	_object_allocator.deallocate(_objects_front, N);
}


//template<class T, int N, class ... Args>
//typename Pool<T, N>::Cls& Pool<T, N>::create(Args&&... args)
//{
//	for (ObjPair& pair : _objects)
//	{
//		if (pair.second == false) // object is not constructed.
//		{
//			pair.second = true;
//			_class_allocator.construct(pair.first, std::forward<Args>(args)...);
//			return pair.first;
//		}
//	}

//	// TODO: throw exception (no free objects in pool).
//	throw 1;
//}



template<class T, int N>
void Pool<T, N>::clear(Pool<T, N>::Cls& instance)
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

	// TODO: throw exception (objects is not from pool).
	throw 1;
}


template<class T, int N>
void Pool<T, N>::clear()
{
	for (ObjPair& pair : _objects)
	{
		pair.second = false;
		_object_allocator.destroy(pair.first);
	}
}


// __OBJECT_POOL_H__
#endif

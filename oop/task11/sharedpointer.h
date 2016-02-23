#ifndef __SHAREDPOINTER_H__
#define __SHAREDPOINTER_H__


template<class Type>
class SharedPointer
{
	public:
		typedef Type* pointer_t;
		typedef Type& reference_t;

		// Constructors / Destructor.
		SharedPointer(pointer_t ptr = nullptr);
		SharedPointer(const SharedPointer& sptr);
		SharedPointer(SharedPointer&& sptr);
		~SharedPointer();

		// Operators.
		SharedPointer& operator=(pointer_t ptr);
		SharedPointer& operator=(const SharedPointer& sptr);
		SharedPointer& operator=(SharedPointer&& sptr);

		bool operator==(const pointer_t ptr) const;
		bool operator==(const SharedPointer& sptr) const;

		// Getters.
		pointer_t get_pointer();
		const pointer_t get_pointer() const;

		reference_t get_reference();
		const reference_t get_reference() const;

		bool is_null() const;
		size_t get_shares_num() const;

		// Methods.
		void release();

	private:
		// Inner class.
		struct PointerDestructor
		{
			PointerDestructor(pointer_t ptr, size_t num = 1)
				: pointer(ptr),
				  shares_num(num) {}
			PointerDestructor(const PointerDestructor& ps)
				: pointer(ps.pointer),
				  shares_num(ps.shares_num) {}
			~PointerDestructor()
			{
				delete pointer;
			}

			pointer_t pointer;
			size_t shares_num;
		};

		// Fileds.
		PointerDestructor* _ptr_destructor;
};


template<class Type>
SharedPointer<Type>::SharedPointer(SharedPointer::pointer_t ptr)
	: _ptr_destructor(new PointerDestructor(ptr))
{
}


template<class Type>
SharedPointer<Type>::SharedPointer(const SharedPointer& sptr)
	: _ptr_destructor(sptr._ptr_destructor)
{
	++(_ptr_destructor->shares_num);
}


template<class Type>
SharedPointer<Type>::SharedPointer(SharedPointer&& sptr)
	: _ptr_destructor(sptr._ptr_destructor)
{
	sptr._ptr_destructor = nullptr;
}


template<class Type>
SharedPointer<Type>::~SharedPointer()
{
	release();
}


template<class Type>
SharedPointer<Type>& SharedPointer<Type>::operator=(SharedPointer::pointer_t ptr)
{
	if ((_ptr_destructor->pointer) == ptr)
		return (*this);

	release();
	_ptr_destructor = new PointerDestructor(ptr);

	return (*this);
}


template<class Type>
SharedPointer<Type>& SharedPointer<Type>::operator=(const SharedPointer& sptr)
{
	if (this->operator==(sptr))
		return (*this);

	release();
	_ptr_destructor = sptr._ptr_destructor;
	++(_ptr_destructor->shares_num);

	return (*this);
}


template<class Type>
bool SharedPointer<Type>::operator==(const SharedPointer& sptr) const
{
	return (_ptr_destructor == sptr._ptr_destructor);
}


template<class Type>
typename SharedPointer<Type>::pointer_t SharedPointer<Type>::get_pointer()
{
	return (!is_null()
			? (_ptr_destructor->pointer)
			: nullptr);
}


template<class Type>
const typename SharedPointer<Type>::pointer_t SharedPointer<Type>::get_pointer() const
{
	return (!is_null()
			? (_ptr_destructor->pointer)
			: nullptr);
}


template<class Type>
typename SharedPointer<Type>::reference_t SharedPointer<Type>::get_reference()
{
	return *(_ptr_destructor->pointer);
}


//template<class Type>
//const typename SharedPointer<Type>::reference_t SharedPointer<Type>::get_reference() const
//{
//	return *(_ptr_destructor->pointer);
//}


template<class Type>
bool SharedPointer<Type>::is_null() const
{
	return ((_ptr_destructor == nullptr)
			|| (_ptr_destructor->pointer == nullptr));
}


template<class Type>
size_t SharedPointer<Type>::get_shares_num() const
{
	return (!is_null()
			? (_ptr_destructor->shares_num)
			: 0);
}


template<class Type>
void SharedPointer<Type>::release()
{
	if (_ptr_destructor == nullptr)
		return;

	--(_ptr_destructor->shares_num);

	// TODO: check for nullptr.
	if (_ptr_destructor->shares_num == 0)
		delete _ptr_destructor;

	_ptr_destructor = nullptr;
}


template<class T>
SharedPointer<T> make_shared_pointer(T* ptr)
{
	return SharedPointer<T>(ptr);
}


// __SHAREDPOINTER_H__
#endif

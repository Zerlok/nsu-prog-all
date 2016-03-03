#ifndef __SHAREDPOINTER_H__
#define __SHAREDPOINTER_H__


template<class Type, bool do_copy_on_write = false>
class SharedPointer
{
	public:
		typedef Type* pointer_t;
		typedef Type& reference_t;

		// Constructors / Destructor.
		SharedPointer(pointer_t ptr = nullptr)
			: _ptr_destructor(new PointerDestructor(ptr)) { }

		SharedPointer(const SharedPointer& sptr)
			: _ptr_destructor(sptr._ptr_destructor)
		{
			++(_ptr_destructor->refs_counter);
		}

		SharedPointer(SharedPointer&& sptr)
			: _ptr_destructor(sptr._ptr_destructor)
		{
			sptr._ptr_destructor = nullptr;
		}

		~SharedPointer()
		{
			release();
		}

		// Operators.
		SharedPointer& operator=(pointer_t ptr)
		{
			if ((_ptr_destructor->pure_pointer) == ptr)
				return (*this);

			release();
			_ptr_destructor = new PointerDestructor(ptr);

			return (*this);
		}

		SharedPointer& operator=(const SharedPointer& sptr)
		{
			if (this->operator==(sptr))
				return (*this);

			release();
			_ptr_destructor = sptr._ptr_destructor;
			++(_ptr_destructor->refs_counter);

			return (*this);
		}

		SharedPointer& operator=(SharedPointer&& sptr)
		{
			if (this->operator==(sptr))
				return (*this);

			release();
			_ptr_destructor = sptr._ptr_destructor;
			sptr._ptr_destructor = nullptr;

			return (*this);
		}

		bool operator==(const pointer_t ptr) const
		{
			return (get_pointer() == ptr);
		}

		bool operator==(const SharedPointer& sptr) const
		{
			return (_ptr_destructor == sptr._ptr_destructor);
		}

		const reference_t operator*() const
		{
			return get_reference();
		}

		reference_t operator*()
		{
			return get_reference();
		}

		const pointer_t operator->() const
		{
			return get_pointer();
		}

		pointer_t operator->()
		{
			return get_pointer();
		}

		// Getters.
		pointer_t get_pointer()
		{
			_copy_on_write();
			return (!is_null()
					? (_ptr_destructor->pure_pointer)
					: nullptr);
		}

		const pointer_t get_pointer() const
		{
			return get_const_pointer();
		}

		const pointer_t get_const_pointer() const
		{
			return (!is_null()
					? (_ptr_destructor->pure_pointer)
					: nullptr);
		}

		reference_t get_reference()
		{
			_copy_on_write();
			return *(_ptr_destructor->pure_pointer);
		}

		const reference_t get_reference() const
		{
			return get_const_reference();
		}

		const reference_t get_const_reference() const
		{
			return *(_ptr_destructor->pure_pointer);
		}

		bool is_null() const
		{
			return ((_ptr_destructor == nullptr)
					|| (_ptr_destructor->pure_pointer == nullptr));
		}

		size_t get_references_counter() const
		{
			return (!is_null()
					? (_ptr_destructor->refs_counter)
					: 0);
		}

		// Methods.
		void release()
		{
			if (_ptr_destructor == nullptr)
				return;

			--(_ptr_destructor->refs_counter);
			if (_ptr_destructor->refs_counter == 0)
				delete _ptr_destructor;

			_ptr_destructor = nullptr;
		}


	private:
		/**
		 * @brief The struct with references num and pure pointer destructor.
		 */
		struct PointerDestructor
		{
			PointerDestructor(pointer_t ptr, size_t num = 1)
				: pure_pointer(ptr),
				  refs_counter(num) {}
			~PointerDestructor()
			{
				delete pure_pointer;
			}

			pointer_t pure_pointer;
			size_t refs_counter;
		};

		// Fileds.
		PointerDestructor* _ptr_destructor;

		// Methods.
		void _copy_on_write()
		{
			if (!do_copy_on_write
					|| is_null()
					|| (_ptr_destructor->refs_counter <= 1))
				return;

			--(_ptr_destructor->refs_counter);

			Type* ptr_copy = new Type(*(_ptr_destructor->pure_pointer));
			_ptr_destructor = new PointerDestructor(ptr_copy);
		}
};


template<class Type>
SharedPointer<Type> shared_pointer(Type* ptr)
{
	return std::move(SharedPointer<Type>(ptr));
}


// __SHAREDPOINTER_H__
#endif

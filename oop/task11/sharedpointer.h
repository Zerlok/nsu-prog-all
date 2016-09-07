#ifndef __SHAREDPOINTER_H__
#define __SHAREDPOINTER_H__


template<class Type, bool do_copy_on_write = false>
class SharedPointer
{
	public:
		// Typedefs.
		typedef Type* pointer_t;
		typedef Type& reference_t;

		// Constructors / Destructor.
		SharedPointer(pointer_t ptr = nullptr)
			: _ptr_destructor(new PointerDestructor(ptr)) { }
		SharedPointer(const SharedPointer& sptr)
			: _ptr_destructor(sptr._ptr_destructor)
		{
			++(_ptr_destructor->shares_counter);
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

			reset(ptr);

			return (*this);
		}
		SharedPointer& operator=(const SharedPointer& sptr)
		{
			if (this->operator==(sptr))
				return (*this);

			release();
			_ptr_destructor = sptr._ptr_destructor;
			++(_ptr_destructor->shares_counter);

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
			return (get_cpointer() == ptr);
		}
		bool operator==(const SharedPointer& sptr) const
		{
			return ((_ptr_destructor == sptr._ptr_destructor)
					|| (get_cpointer() == sptr.get_cpointer()));
		}
		operator bool() const
		{
			return !is_null();
		}

		const reference_t operator*() const
		{
			return get_creference();
		}
		const pointer_t operator->() const
		{
			return get_cpointer();
		}

		reference_t operator*()
		{
			return get_reference();
		}
		pointer_t operator->()
		{
			return get_pointer();
		}

		// Getters.
		const pointer_t get_cpointer() const
		{
			return (!is_null()
					? (_ptr_destructor->pure_pointer)
					: nullptr);
		}
		const pointer_t get_pointer() const
		{
			return get_cpointer();
		}
		pointer_t get_pointer()
		{
			_copy_on_write();
			return (!is_null()
					? (_ptr_destructor->pure_pointer)
					: nullptr);
		}

		const reference_t get_creference() const
		{
			return *(_ptr_destructor->pure_pointer);
		}
		const reference_t get_reference() const
		{
			return get_creference();
		}
		reference_t get_reference()
		{
			_copy_on_write();
			return *(_ptr_destructor->pure_pointer);
		}

		bool is_null() const
		{
			return ((_ptr_destructor == nullptr)
					|| (_ptr_destructor->pure_pointer == nullptr));
		}

		size_t get_shares_num() const
		{
			return (!is_null()
					? (_ptr_destructor->shares_counter)
					: 0);
		}

		// Methods.
		void release()
		{
			if (_ptr_destructor == nullptr)
				return;

			--(_ptr_destructor->shares_counter);
			if (_ptr_destructor->shares_counter == 0)
				delete _ptr_destructor;

			_ptr_destructor = nullptr;
		}
		void reset(pointer_t ptr)
		{
			release();
			if (ptr != nullptr)
				_ptr_destructor = new PointerDestructor(ptr);
		}

	private:
		/**
		 * @brief The struct with references num and pure pointer destructor.
		 */
		struct PointerDestructor
		{
			PointerDestructor(pointer_t ptr, size_t num = 1)
				: pure_pointer(ptr),
				  shares_counter(num) {}
			~PointerDestructor()
			{
				delete pure_pointer;
			}

			pointer_t pure_pointer;
			size_t shares_counter;
		};

		// Fileds.
		PointerDestructor* _ptr_destructor;

		// Methods.
		void _copy_on_write()
		{
			if (!do_copy_on_write
					|| is_null()
					|| (_ptr_destructor->shares_counter <= 1))
				return;

			--(_ptr_destructor->shares_counter);

			Type* ptr_copy = new Type(get_creference());
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

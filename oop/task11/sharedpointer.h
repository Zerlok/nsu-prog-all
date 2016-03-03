#ifndef __SHAREDPOINTER_H__
#define __SHAREDPOINTER_H__


struct DefaultDestroyer
{
	template<class Type>
	void operator()(Type* ptr) { delete ptr; }
};


struct ArrayDestroyer
{
	template<class Type>
	void operator()(Type* ptr) { delete[] ptr; }
};


struct VoidDestroyer
{
	template<class Type>
	void operator()(Type*) { }
};


template<class Type, class Destroyer = DefaultDestroyer>
class SharedPointer
{
	public:
		typedef Type* pointer_t;
		typedef Type& reference;

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

		// Getters.
		pointer_t get_pointer()
		{
			return (!is_null()
					? (_ptr_destructor->pure_pointer)
					: nullptr);
		}

		const pointer_t get_pointer() const
		{
			return (!is_null()
					? (_ptr_destructor->pure_pointer)
					: nullptr);
		}

		reference get_reference()
		{
			return *(_ptr_destructor->pure_pointer);
		}

		const reference get_reference() const
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
			PointerDestructor(const PointerDestructor& ps)
				: pure_pointer(ps.pure_pointer),
				  refs_counter(ps.refs_counter) {}
			~PointerDestructor()
			{
				destroyer(pure_pointer);
			}

			pointer_t pure_pointer;
			size_t refs_counter;
			Destroyer destroyer;
		};

		// Fileds.
		PointerDestructor* _ptr_destructor;
};


template<class Type>
SharedPointer<Type> shared_pointer(Type* ptr)
{
	return std::move(SharedPointer<Type>(ptr));
}


// __SHAREDPOINTER_H__
#endif

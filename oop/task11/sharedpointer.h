#ifndef __SHAREDPOINTER_H__
#define __SHAREDPOINTER_H__


#include <stddef.h>
#include <utility>


template<class Type>
class SharedPointer
{
	public:
		// Typedefs.
		using pointer_t = Type*;
		using reference_t = Type&;
		using cpointer_t = Type const*;
		using creference_t = const Type&;

		// Constructors / Destructor.
		SharedPointer(pointer_t ptr = nullptr)
			: _ptr_destructor(new PointerDestructor(ptr))
		{
		}
		SharedPointer(const SharedPointer& sptr)
			: _ptr_destructor(sptr._ptr_destructor)
		{
			if (_ptr_destructor != nullptr)
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
			if (this->operator==(ptr))
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

		bool operator==(pointer_t ptr) const
		{
			return (get_pointer() == ptr);
		}
		bool operator==(cpointer_t ptr) const
		{
			return (get_cpointer() == ptr);
		}
		bool operator==(const SharedPointer& sptr) const
		{
			return (get_cpointer() == sptr.get_cpointer());
		}

		bool operator!=(pointer_t ptr) const
		{
			return (!this->operator==(ptr));
		}
		bool operator!=(cpointer_t ptr) const
		{
			return (!this->operator==(ptr));
		}
		bool operator!=(const SharedPointer& sptr) const
		{
			return (!this->operator==(sptr));
		}

		operator bool() const
		{
			return !is_null();
		}

		creference_t operator*() const
		{
			return get_creference();
		}
		cpointer_t operator->() const
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
		cpointer_t get_cpointer() const
		{
			return (!is_null()
					? (_ptr_destructor->pure_pointer)
					: nullptr);
		}
		cpointer_t get_pointer() const
		{
			return get_cpointer();
		}
		pointer_t get_pointer()
		{
			return (!is_null()
					? (_ptr_destructor->pure_pointer)
					: nullptr);
		}

		creference_t get_creference() const
		{
			return *(_ptr_destructor->pure_pointer);
		}
		creference_t get_reference() const
		{
			return get_creference();
		}
		reference_t get_reference()
		{
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
			_ptr_destructor = new PointerDestructor(ptr);
		}

	private:
		/**
		 * @brief The struct with references num and pure pointer destructor.
		 */
		struct PointerDestructor
		{
			PointerDestructor(pointer_t ptr, const size_t& num = 1)
				: pure_pointer(ptr),
				  shares_counter(num) {}
			~PointerDestructor()
			{
				if (pure_pointer != nullptr)
					delete pure_pointer;
			}

			pointer_t pure_pointer;
			size_t shares_counter;
		};

		// Fileds.
		PointerDestructor* _ptr_destructor;
};


template<class Type>
SharedPointer<Type> shared_pointer(typename SharedPointer<Type>::pointer_t ptr)
{
	return std::move(SharedPointer<Type>(ptr));
}


// __SHAREDPOINTER_H__
#endif

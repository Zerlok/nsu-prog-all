#include <iostream>


template <class Pointer>
class AutoPointer
{
	public:
		AutoPointer() : _ptr(NULL) {};
		~AutoPointer() { delete _ptr; }
		
		AutoPointer(Pointer *p) : _ptr(p) {};		
		
		AutoPointer(AutoPointer& auto_ptr)
		{
			reset(auto_ptr.release());
		}

		Pointer *release()
		{
			Pointer *tmp = _ptr;
			_ptr = NULL;

			return tmp;
		}

		Pointer *reset(Pointer *p)
		{
			delete _ptr;

			_ptr = p;

			return _ptr;
		}

		AutoPointer& operator=(AutoPointer& auto_ptr)
		{
			delete _ptr;
			_ptr = auto_ptr._ptr;
		}
		
		Pointer& operator*() const
		{
			return (*_ptr);
		}

		Pointer *operator->() const
		{
			return _ptr;
		}

	private:
		Pointer *_ptr;
};


class A
{
	public:
		A() { std::cout << "A : Constr" << std::endl; }
		~A() { std::cout << "A : Destr" << std::endl; }
};


void call_throw()
{
	AutoPointer<A> ptr(new A());
}


int main(int argc, char **argv)
{
	call_throw();
	return 0;
};
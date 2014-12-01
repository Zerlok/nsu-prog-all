#include <iostream>


AutoPointer::AutoPointer() : _ptr(NULL)
{
}


AutoPointer::~AutoPointer()
{
	delete _ptr;
}

		
AutoPointer::AutoPointer(Pointer *p) : _ptr(p)
{
}

		
AutoPointer::AutoPointer(AutoPointer& auto_ptr)
{
	reset(auto_ptr.release());
}


Pointer *AutoPointer::release()
{
	Pointer *tmp = _ptr;
	_ptr = NULL;

	return tmp;
}


Pointer *AutoPointer::reset(Pointer *p)
{
	delete _ptr;

	_ptr = p;

	return _ptr;
}


AutoPointer& AutoPointer::operator=(AutoPointer& auto_ptr)
{
	delete _ptr;
	_ptr = auto_ptr._ptr;
}

		
Pointer& AutoPointer::operator*() const
{
	return (*_ptr);
}


Pointer *AutoPointer::operator->() const
{
	return _ptr;
}

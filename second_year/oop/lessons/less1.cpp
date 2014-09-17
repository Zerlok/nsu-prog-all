#include <cstdlib>
#include <iostream>
#include "array.h"


int Array::_check_and_expand_an_array()
{
	if (data_end >= length)
	{
		length *= 2;
		data = (int*)realloc(data, length);

		if (data == NULL)
		{
			return -1;
		}
	}
	else
	{
		return 1;
	}

	return 0;
}


Array & Array::operator=(const Array &array)
{
	data_end = array.data_end;
	_check_and_expand_an_array();

	for (int i = 0; i < data_end; i++)
	{
		data[i] = array.data[i];
	}
}

int Array::operator==(const Array &array)
{
	if (data_end != array.data_end)
	{
		return 0;
	}

	for (int i = 0; i < data_end; i++)
	{
		if (data[i] != data[i])
		{
			return 0;
		}
	}

	return 1;
}

int Array::operator[](const int indx)
{
	if (indx >= data_end and indx < 0)
	{
		std::cout << "IndexError!";
		return indx;
	}

	return data[indx];
}

std::ostream & operator<<(std::ostream & output, const Array & array)
{
	output << "[";
	for (int i = 0; i < array.data_end; i++)
	{
		output << array.data[i] << ", ";
	}
	output << "\b\b] (" << array.data_end << ", " << array.length << ")";
	return output;
}

int Array::len()
{
	return data_end;
}

int Array::insert(int indx, int value)
{
	if (indx > data_end)
	{
		return 1;
	}

	data_end += 1; // Increment the data size

	_check_and_expand_an_array(); // Check for allocated memmory

	for (int i = data_end; i > indx; i--) // Shift values to right
	{
		data[i] = data[i-1];
	}

	data[indx] = value; // Insert the new value

	return 0;
}

int Array::push_back(int value)
{
	_check_and_expand_an_array();

	data[data_end] = value;
	data_end++;

	return 0;
}


// The functions names is the same as the class name.
// And they have no returning type.
		
// Constructor
Array::Array(int _length)
{
	if (_length > 0)
	{
	}
	
	data_end = 0;
	length = _length > 0 ? _length : 1;
	data = new int[length];
	// std::cout << "The new array was created successfully!" << std::endl;
}

// Destructor
Array::~Array()
{
	delete data;	
	// std::cout << "This array was deleted successfully!" << std::endl;
}

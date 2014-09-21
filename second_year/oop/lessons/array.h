#ifndef __ARRAY_H__
#define __ARRAY_H__

#include <cstdlib>
#include <iostream>


class Array
{
	private:
		int *data;
		int data_end;
		int length;

		int _check_and_expand_an_array();

	public:
		Array & operator=(const Array &array);
		int operator==(const Array &array);
		int operator[](const int indx);
		friend std::ostream & operator<<(std::ostream & output, const Array & array);

		int len();
		int insert(int indx, int value);
		int push_back(int value);

		// The functions names is the same as the class name.
		// And they have not the returning type.
		
		// Constructor
		Array(int _length);

		// Destructor
		~Array();
};

std::ostream& operator<<(std::ostream & output, const Array & array);

#endif
#include <cstdlib>
#include <iostream>


class Array
{
	private:
		int *data;
		int data_end;
		int length;

		int check_and_expand_an_array()
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


	public:
		Array & operator=(const Array &array)
		{
			data_end = array.data_end;
			check_and_expand_an_array();

			for (int i = 0; i < data_end; i++)
			{
				data[i] = array.data[i];
			}
		}

		int len()
		{
			return data_end;
		}

		int insert(int indx, int value)
		{
			if (indx > data_end)
			{
				return 1;
			}

			data_end += 1; // Increment the data size

			check_and_expand_an_array(); // Check for allocated memmory

			for (int i = data_end; i > indx; i--) // Shift values to right
			{
				data[i] = data[i-1];
			}

			data[indx] = value; // Insert the new value

			return 0;
		}

		int push_back(int value)
		{
			check_and_expand_an_array();

			data[data_end] = value;
			data_end++;

			return 0;
		}

		void show()
		{
			int i;

			std::cout << std::endl << "[ ";
			
			for (i = 0; i < data_end; i++)
			{
				std::cout << data[i] << " ";
			}

			std::cout << "] (" << data_end << ", " << length << ")" << std::endl;
			// std::cout << "Data length: " << data_end << ", Allocated length: " << length << std::endl;
		}

		// The functions names is the same as the class name.
		// And they do not has the returning type.
		
		// Constructor
		Array(int _length)
		{
			if (_length > 0)
			{
				data = new int[_length];
				length = _length;
				data_end = 0;
			
				std::cout << "The new array was created successfully!" << std::endl;

				show();
			}
		}

		// Destructor
		~Array()
		{
			show();

			delete data;
			
			std::cout << "This array was deleted successfully!" << std::endl;
		};
};


int main()
{
	Array arr1(10), arr2(20);

	for (int i = 1; i < 5; i++)
	{
		arr1.push_back(i);
	}

	arr1.show();
	arr2 = arr1;
	
	arr1.insert(2, -100);

	arr1.show();
	arr2.show();

	return 0;
}
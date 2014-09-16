#include <cstdio>
#include <cstdlib>


class Array
{
	private:

		int *data;
		int data_end;
		int length;

	public:

		int len()
		{
			return data_end;
		}

		int push_back(int value)
		{
			if (data_end == length)
			{
				length *= 2;
				data = (int*)realloc(data, length);

				if (data == NULL)
				{
					return 1;
				}
			}

			data[data_end] = value;
			data_end++;

			return 0;
		}

		void show()
		{
			int i;

			printf("[ ");
			
			for (i = 0; i < data_end; i++)
			{
				printf("%d ", data[i]);
			}

			printf("]\n");

			printf("Data length: %d, Allocated length: %d\n", data_end, length);
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
			
				printf("The new array was created successfully!\n");

				show();
			}
		}

		// Destructor
		~Array()
		{
			show();

			delete data;
			
			printf("This array was deleted successfully!\n");
		};
};


int main()
{
	Array arr(10);

	// arr.show();

	for (int i = 1; i < 5; i++)
	{
		arr.push_back(i);
	}

	// arr.show();

	return 0;
}
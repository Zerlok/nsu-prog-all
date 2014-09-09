#include <iostream>


using namespace std;


class NSUStudent
{
	private:
		unsigned int hash;
		string key;

		struct StudentValues
		{
			unsigned age;
			float average_mark;
		};

	public:
		NSUStudent(unsigned int input_hash, string input_key, unsigned int input_age, float input_mark)
		{
			StudentValues value;

			hash = input_hash;
			key = input_key;
			value.age = input_age;
			value.average_mark = input_mark;
		};

		void print()
		{
			cout << "My name is " << key << endl;
		};

		void debug_print()
		{
			cout << "hash: " << hash << endl << "key: " << key << endl;
		};

		~NSUStudent();
};


unsigned int get_hashed(string key)
{
	return 0;
}


int main()
{
	NSUStudent *student = new NSUStudent(10, "Danil Troshnev", 19, 2.0);

	student->debug_print();

	return 0;
}

#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

class Person
{
	public:
		Person() { std::cout << "PersonCreator" << std::endl; }
		~Person() { std::cout << "PersonDestuctor" << std::endl; }
		// virtual ~Person() { std::cout << "PersonDestuctor" << std::endl; }

	private:
		std::string name;
};

class Student : public Person
{
	public:
		Student()
		{
			std::cout << "Student data creating..." << std::endl;
			someData = new char[100];
		}
		~Student()
		{
			std::cout << "Student data deleting..." << std::endl;
			delete someData;
		}
	
	private:
		char *someData;
};


void read_data()
{
	std::vector<int> v(5);

	std::copy(
			std::istream_iterator<int>(std::cin),
			std::istream_iterator<int>(),
			std::back_inserter(v)
	);

	std::sort(v.begin(), v.end());

	std::copy(
			v.begin(),
			v.end(),
			std::ostream_iterator<int>(std::cout, " ")
	);

	std::cout << std::endl;
}


int main(int argc, char **argv)
{
	// read_data();

	std::cout << (int*)3 + 5 << std::endl;

	return 0;
}
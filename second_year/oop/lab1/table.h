#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <iostream>
#include <cstring>
#include <cstdlib>


/* ERRORS MESSAGES */
#define ERR_BAD_ALLOC "Not enough memmory!"
#define ERR_KEY_NOT_SET "This key is not set yet!"


typedef std::string String;


/* STUDENT CLASS */
class Student
{
	private:
		String name;
		unsigned int age;
		unsigned int course;
		float average_mark;			
		String department;

	public:
		Student(const String _name);
		Student(const String _name, const unsigned int _age, const unsigned int _course, const float _average_mark, const String _department);
		~Student();

		Student(const Student& s);

		/* Get Field */
		String get_name() { return name; }
		unsigned int get_age() { return age; }
		unsigned int get_course() { return course; }
		float get_average_mark() { return average_mark; }
		String get_department() { return department; }

		/* Set Field */
		void set_name(const String _name) { this->name = _name; }
		void set_age(const unsigned int _age) { this->age = _age; }
		void set_course(const unsigned int _course) { this->course = _course; }
		void set_average_mark(const float _average_mark) { this->average_mark = _average_mark; }
		void set_department(const String _department) { this->department = _department; }

		/* Operators */
		Student& operator=(const Student& s);
		friend bool operator==(const Student& s1, const Student& s2);
		friend bool operator!=(const Student& a, const Student& b);

		/* DEBUG */
		void show()
		{
			std::cout << "Student: " << name << std::endl
					<< "|  Age  |  Course  |  Mark  |  Dep. |" << std::endl
					<< "|" << age << "|" << course << "|" << average_mark
					<< "|" << department << "|" << std::endl << std::endl;
		}
};

bool operator==(const Student& a, const Student& b);
bool operator!=(const Student& a, const Student& b);


/* ITEM CLASS */
class Item
{
	private:
		String key; // Key (name)
		Student *value; // Pointer to Student object ()
		Item *next; // Next Item object with same hash (for collisions)

	public:
		Item(const String _key);
		Item(Student& _student);
		Item(const String _key, Student& _student);
		~Item();

		Item(const Item& i);

		/* Get Field */
		Student& get_value() const;
		Item& get_next() const;

		/* Operators */
		Item& operator=(const Item& i);
		friend bool operator==(const Item& a, const Item& b);
		friend bool operator!=(const Item& a, const Item& b);
		
		/* Methods */
		bool push_back(Item& i); // Sets Next field
		bool is_empty() const;

		/* DEBUG */
		void show()
		{
			std::cout << "Item: " << key << std::endl;
			std::cout << "next : " << next << std::endl;
			std::cout << "contains: ";
			if (value != NULL)
			{	
				value->show();
			}
			else
			{
				std::cout << "null" << std::endl;
			}
		}
};

bool operator==(const Item& a, const Item& b);
bool operator!=(const Item& a, const Item& b);


/* HASHTABLE CLASS */
// class HashTable
// {
// 	private:
// 		Item **data; // List of pointers to Item objects
// 		int data_end; // Cells of allocated memory

// 	public:
// 		// Constructor / Destructor
// 		HashTable();
// 		~HashTable();

// 		HashTable(int _mem);
// 		HashTable(const HashTable& b);

// 		/* Get Fields */
// 		Item& at(const String& key);
// 		const Item& at(const String& key) const;
// 		size_t size() const;
// 		bool empty() const;

// 		/* Operators */
// 		Item& operator[](const String& key);
// 		HashTable& operator=(const HashTable& b);
// 		friend bool operator==(const HashTable& a, const HashTable& b);
// 		friend bool operator!=(const HashTable& a, const HashTable& b);

// 		/* Methods */
// 		void swap(HashTable& b);
// 		void clear();
// 		bool erase(const String& key);
// 		bool insert(const String& key, const Item& value);
// 		bool contains(const String& key) const;
// };

// bool operator==(const HashTable& a, const HashTable& b);
// bool operator!=(const HashTable& a, const HashTable& b);


/* ACCESSORY FUNCTIONS IMAGES */
unsigned int hash(String key);

#endif
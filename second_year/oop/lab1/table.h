#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>


/* ERRORS MESSAGES */
#define ERR_BAD_ALLOC "Not enough memmory!"
#define ERR_KEY_NOT_FOUND "The key was not found!"


typedef std::string String;


/* STUDENT CLASS */
class Value
{
	public:
		/* Constructors / Destructor */
		Value(
			const String& name, // Main field (Should be defined always!).
			const unsigned int age=18,
			const unsigned int course=1,
			const float average_mark=4.0,
			const String& department="IT"
		);

		~Value();

		Value(const Value& s); // Copy student.

		/* Get Field */
		String get_name() const { return _name; }
		unsigned int get_age() const { return _age; }
		unsigned int get_course() const { return _course; }
		float get_average_mark() const { return _average_mark; }
		String get_department() const { return _department; }

		/* Set Field */
		void set_name(const String& name) { _name = name; }
		void set_age(const unsigned int age) { _age = age; }
		void set_course(const unsigned int course) { _course = course; }
		void set_average_mark(const float average_mark) { _average_mark = average_mark; }
		void set_department(const String& department) { _department = department; }

		/* Operators */
		Value& operator=(const Value& value);
		friend bool operator==(const Value& value1, const Value& value2);
		friend bool operator!=(const Value& value1, const Value& value2);

		/* DEBUG */
		void show() const // Prints student fields to console.
		{
			std::cout << "Value: " << _name << std::endl
					<< "|  Age  |  Course  |  Mark  |  Dep. |" << std::endl
					<< "|" << _age << "|" << _course << "|" << _average_mark
					<< "|" << _department << "|" << std::endl << std::endl;
		}

	private:
		/* Fields */
		String _name;
		unsigned int _age;
		unsigned int _course;
		float _average_mark;			
		String _department;
};

bool operator==(const Value& a, const Value& b);
bool operator!=(const Value& a, const Value& b);


/* ITEM CLASS */
class Item
{
	public:
		/* Constructors / Desctructor */
		Item(const String& key);
		Item(const Value& value);
		Item(const String& key, const Value& value);
		~Item();

		Item(const Item& i);

		/* Get Field */
		String get_key() const { return _key; }
		Value& get_value();
		Item *get_next() const;
		
		/* Set Field */
		void set_next(Item *item);

		/* Operators */
		Item& operator=(const Item& item);
		friend bool operator==(const Item& value1, const Item& value2);
		friend bool operator!=(const Item& value1, const Item& value2);
		
		/* Methods */
		bool push_back(Item& item); // Pushes back an Item object.
		bool push_chain(Item& item); // Links a chain of Item objects (except first item!).
		bool is_empty() const;	// Is an empty Item object.

		/* DEBUG */
		void show() const // Prints Item fields to console.
		{
			std::cout << "Item: " << _key << std::endl;
			std::cout << "next : " << _next << std::endl;
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
	
	private:
		/* Fields */
		String _key; // Key (the Student name)
		Value *_value; // Pointer to Value object.
		Item *_next; // Next Item object with same hash (for collisions)
};

bool operator==(const Item& a, const Item& b);
bool operator!=(const Item& a, const Item& b);


/* HASHTABLE CLASS */
class HashTable
{
	public:
		// Constructors / Destructor
		HashTable(int _mem=1000);
		~HashTable();

		HashTable(const HashTable& b);

		/* Get Field */
		Value& at(const String& key);
		const Value& at(const String& key) const;
		size_t size() const;
		bool empty() const;

		/* Operators */
		Value& operator[](const String& key);
		HashTable& operator=(const HashTable& b);
		friend bool operator==(const HashTable& a, const HashTable& b);
		friend bool operator!=(const HashTable& a, const HashTable& b);

		/* Methods */
		void swap(HashTable& b);
		void clear();
		bool erase(const String& key);
		bool insert(const String& key, const Value& value);
		bool contains(const String& key) const;

	private:
		/* Fields */
		Item **data; // List of pointers to Item objects
		int data_end; // Cells of allocated memory
		
		/* Methods */
		int get_index(const String& key) const; // Counts index of item in hashtable
};

bool operator==(const HashTable& a, const HashTable& b);
bool operator!=(const HashTable& a, const HashTable& b);


/* ACCESSORY FUNCTIONS IMAGES */
unsigned int hash(const String& key); // Hash function

#endif
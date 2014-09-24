#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <stdexcept>


/* ERRORS MESSAGES */
#define ERR_BAD_ALLOC "Not enough memmory!"


typedef std::string String;


/* STUDENT CLASS */
class Value
{
	private:
		/* Fields */
		String name;
		unsigned int age;
		unsigned int course;
		float average_mark;			
		String department;

	public:
		/* Constructors / Destructor */
		Value(const String& _name);
		Value(const String& _name, const unsigned int _age, const unsigned int _course, const float _average_mark, const String& _department);
		~Value();

		Value(const Value& s);

		/* Get Field */
		String get_name() const { return name; }
		unsigned int get_age() const { return age; }
		unsigned int get_course() const { return course; }
		float get_average_mark() const { return average_mark; }
		String get_department() const { return department; }

		/* Set Field */
		void set_name(const String& _name) { this->name = _name; }
		void set_age(const unsigned int _age) { this->age = _age; }
		void set_course(const unsigned int _course) { this->course = _course; }
		void set_average_mark(const float _average_mark) { this->average_mark = _average_mark; }
		void set_department(const String& _department) { this->department = _department; }

		/* Operators */
		Value& operator=(const Value& s);
		friend bool operator==(const Value& s1, const Value& s2);
		friend bool operator!=(const Value& a, const Value& b);

		/* DEBUG */
		void show() const
		{
			std::cout << "Value: " << name << std::endl
					<< "|  Age  |  Course  |  Mark  |  Dep. |" << std::endl
					<< "|" << age << "|" << course << "|" << average_mark
					<< "|" << department << "|" << std::endl << std::endl;
		}
};

bool operator==(const Value& a, const Value& b);
bool operator!=(const Value& a, const Value& b);


/* ITEM CLASS */
class Item
{
	private:
		/* Fields */
		String key; // Key (name)
		Value *value; // Pointer to Value object ()
		Item *next; // Next Item object with same hash (for collisions)

	public:
		/* Constructors / Desctructor */
		Item(const String& _key);
		Item(const Value& _value);
		Item(const String& _key, const Value& _value);
		~Item();

		Item(const Item& i);

		/* Get Field */
		String get_key() const { return key; }
		Value& get_value();
		Item *get_next() const;
		
		/* Set Field */
		void set_next(Item *i);

		/* Operators */
		Item& operator=(const Item& i);
		friend bool operator==(const Item& a, const Item& b);
		friend bool operator!=(const Item& a, const Item& b);
		
		/* Methods */
		bool push_back(Item& i); // Adds i item object to next
		bool push_node(Item& i); // Pushes back i node (except first item!)
		bool is_empty() const;	// Is empty object

		/* DEBUG */
		void show() const
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
class HashTable
{
	private:
		/* Fields */
		Item **data; // List of pointers to Item objects
		int data_end; // Cells of allocated memory
		
		/* Methods */
		int get_index(const String& key) const; // Counts index of item in hashtable

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
};

bool operator==(const HashTable& a, const HashTable& b);
bool operator!=(const HashTable& a, const HashTable& b);


/* ACCESSORY FUNCTIONS IMAGES */
unsigned int hash(const String& key); // Hash function

#endif
#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__


#include <iostream>
#include <stdexcept>
#include <cstring>
// #include <cstdlib>


typedef std::string String;


/* DEBUG */
const bool DEBUG = true;


/* ERRORS MESSAGES */
static const char *ERR_BAD_ALLOC = "Not enough memmory!";
static const char *ERR_KEY_NOT_FOUND = "The key was not found!";


/* VALUE CLASS (a student used as value) */
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

		/* Operators */
		Value& operator=(const Value& value);
		friend bool operator==(const Value& value1, const Value& value2);
		friend bool operator!=(const Value& value1, const Value& value2);

		/* Methods */
		String get_name() const { return _name; }
		String as_string() const;

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
		String _name; // Student name.
		unsigned int _age; // Student age.
		unsigned int _course; // Student course at university.
		float _average_mark; // Student average mark at university.
		String _department; // Student department at university.
};

bool operator==(const Value& value1, const Value& value2);
bool operator!=(const Value& value1, const Value& value2);


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
			if (_value != NULL)
			{	
				_value->show();
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

bool operator==(const Item& value1, const Item& value2);
bool operator!=(const Item& value1, const Item& value2);


/* HASHTABLE CLASS */
class HashTable
{
	public:
		// Constructors / Destructor
		HashTable(int mem=1000);
		~HashTable();

		HashTable(const HashTable& hashtable);

		/* Get Field */
		Value& at(const String& key);
		const Value& at(const String& key) const;
		bool empty() const;
		size_t size() const;

		/* Operators */
		Value& operator[](const String& key);
		HashTable& operator=(const HashTable& hashtable);
		friend bool operator==(const HashTable& value1, const HashTable& value2);
		friend bool operator!=(const HashTable& value1, const HashTable& value2);

		/* Methods */
		void clear();
		bool contains(const String& key) const;
		bool erase(const String& key);
		bool insert(const String& key, const Value& value);
		void swap(HashTable& b);

	private:
		/* Fields */
		Item **_data; // Array of pointers to Item object.
		int _data_end; // Number of cells.
		
		/* Methods */
		int get_index(const String& key) const; // Counts index of item in hashtable
};

bool operator==(const HashTable& value1, const HashTable& value2);
bool operator!=(const HashTable& value1, const HashTable& value2);


/* ACCESSORY FUNCTIONS IMAGES */
unsigned int hash(const String& key); // Hash function (for collision tests).
int good_hash(const String& key); // Good hash function.

#endif
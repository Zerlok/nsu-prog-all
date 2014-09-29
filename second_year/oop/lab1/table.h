#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__


#include <stdexcept>
#include <sstream>


typedef std::string String;


/* DEBUG */
const bool DEBUG = true;
const bool DEBUG_SUPER = false;


/* ERRORS MESSAGES */
static const char *ERR_BAD_ALLOC = "Not enough memmory!";
static const char *ERR_KEY_NOT_FOUND = "The key was not found!";
static const char *ERR_NO_VALUE_IN_ITEM = "The Item object has no value!";


/* VALUE CLASS (a student used as value) */
class Value
{
	public:
		/* Constructors / Destructor */
		Value(
			const String& name, // Main field (Should be defined always!).
			const unsigned int age=18,
			const unsigned int course=1,
			const String& department="IT"
		);

		~Value();

		Value(const Value& s); // Copy student.

		/* Operators */
		friend bool operator==(const Value& value1, const Value& value2);
		friend bool operator!=(const Value& value1, const Value& value2);

		/* Methods */
		String get_name() const { return _name; }
		String as_string() const; // For DEBUG.

	private:
		/* Fields */
		String _name; // Student name.
		unsigned int _age; // Student age.
		unsigned int _course; // Student course at university.
		String _department; // Student department at university.
};

bool operator==(const Value& value1, const Value& value2);
bool operator!=(const Value& value1, const Value& value2);


/* ITEM CLASS */
class Item
{
	public:
		/* Constructors / Desctructor */
		Item(const Value& value);
		Item(const String& key, const Value& value);
		~Item();

		Item(const Item& i);

		/* Get Field */
		bool is_key_equals(const String& key) const;
		bool is_key_not_equals(const String& key) const;
		Item *get_next() const;
		Value& get_value();
		const Value& get_value() const;

		/* Operators */
		friend bool operator==(const Item& value1, const Item& value2);
		friend bool operator!=(const Item& value1, const Item& value2);
		
		/* Methods */
		bool push_back(Item *item); // Pushes back an Item object.
		bool push_back(Item& item); // Pushes back an Item object.
		String as_string() const; // For debug.
	
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

		/* Operators */
		Value& operator[](const String& key);
		HashTable& operator=(const HashTable& hashtable);
		friend bool operator==(const HashTable& value1, const HashTable& value2);
		friend bool operator!=(const HashTable& value1, const HashTable& value2);

		/* Methods */
		void clear();
		bool erase(const String& key);
		Value& get(const String& key);
		const Value& get(const String& key) const;
		size_t get_size() const;
		bool insert(const String& key, const Value& value);
		bool is_empty() const;
		bool is_contains(const String& key) const;
		void swap(HashTable& b);

	private:
		/* Fields */
		Item **_data; // Array of pointers to Item object.
		int _data_end; // Number of cells.
		
		/* Methods */
		int _get_index(const String& key) const; // Counts index of Item in hashtable.
		Value *_search(const String& key) const;
};

bool operator==(const HashTable& value1, const HashTable& value2);
bool operator!=(const HashTable& value1, const HashTable& value2);


/* ACCESSORY FUNCTIONS IMAGES */
unsigned int hash(const String& key); // Hash function (for collision tests).
int good_hash(const String& key); // Good hash function.

#endif
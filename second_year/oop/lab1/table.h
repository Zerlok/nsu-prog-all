#ifndef __HASHTABLE_H__
#define __HASHTABLE_H__


/* -------------- __HASHTABLE_H__ SETUP -------------- */

#include <stdexcept>
#include <sstream>


/* -------------- DEBUG SETTINGS -------------- */

// #define __HTABLE_DEBUG__


/* -------------- CONSTANTS -------------- */

typedef std::string String;
static const int MEM_INIT = 997;
static const int FULLNESS_FACTOR = 2;


/* -------------- ERRORS MESSAGES -------------- */

static const char *ERR_BAD_ALLOC = "Not enough memmory!";
static const char *ERR_BAD_HTABLE_SIZE = "Invalid size of hashtable!";
static const char *ERR_KEY_NOT_FOUND = "The key was not found!";
static const char *ERR_NO_VALUE_IN_ITEM = "The Item object has no value!";


/* -------------- VALUE CLASS (a student used as value) -------------- */

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

		Value(const Value& s);

		/* Operators */
		Value& operator=(const Value& value);
		friend bool operator==(const Value& value1, const Value& value2);
		friend bool operator!=(const Value& value1, const Value& value2);

		/* Methods */
		const String& return_name() const;
		const String& as_string() const;

	private:
		/* Fields */
		String _name; // Student name.
		unsigned int _age; // Student age.
		unsigned int _course; // Student course at university.
		String _department; // Student department at university.
};

bool operator==(const Value& value1, const Value& value2);
bool operator!=(const Value& value1, const Value& value2);


/* -------------- ITEM CLASS -------------- */

class Item
{
	public:
		/* Constructors / Desctructor */
		Item(const Value& value);
		Item(const String& key, const Value& value);
		~Item();

		Item(const Item& i);

		/* Get Field */
		Item *get_next() const;
		String return_key();
		Value& return_value();
		const String return_key() const;
		const Value& return_value() const;

		/* Operators */
		friend bool operator==(const Item& value1, const Item& value2);
		friend bool operator!=(const Item& value1, const Item& value2);
		
		/* Methods */
		bool is_key_equals(const String& key) const;
		bool is_key_not_equals(const String& key) const;
		bool push_back(Item *item);
		bool push_back(Item& item);

	private:
		/* Fields */
		String _key; // Key (the Student name).
		Value *_value; // Pointer to the Value object.
		Item *_next; // Next Item object with the same hash (collisions).
};

bool operator==(const Item& value1, const Item& value2);
bool operator!=(const Item& value1, const Item& value2);


/* -------------- HASHTABLE CLASS -------------- */

class HashTable
{
	public:
		/* Constructors / Destructor */
		HashTable(int mem=MEM_INIT);
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
		int _cells_num; // Number of cells in array.
		int _critical_items_num; // Critical number of Items object in hashtable to expand it.
		
		/* Methods */
		int _get_index(const String& key) const;
		Value *_search(const String& key) const;
		bool _check_and_expand();
};

bool operator==(const HashTable& value1, const HashTable& value2);
bool operator!=(const HashTable& value1, const HashTable& value2);


/* -------------- ACCESSORY FUNCTIONS -------------- */

int hash(const String& key);


/* -------------- __HASHTABLE_H__ END -------------- */
#endif

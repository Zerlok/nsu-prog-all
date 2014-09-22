#ifndef __TABLE_H__
#define __TABLE_H__

#include <iostream>
#include <cstring>
#include <cstdlib>


#define ERR_BAD_ALLOC "Not enough memmory!"
#define ERR_KEY_NOT_SET "This key is not set yet!"


typedef std::string String;


struct Value
{
	String name = "hi"; // Key
	Value *next; // For collisions (list of elements with same hashes)

	/* Info fields */
	unsigned int age;
	unsigned int course;
	unsigned int average_mark;			
	String department;
};


class HashTable
{
	private:
		Value **data; // List of Value structures
		unsigned int data_end; // Cells of allocated memory

	public:
		// Constructor / Destructor
		HashTable();
		~HashTable();

		HashTable(const HashTable& b);

		void swap(HashTable& b);

		HashTable& operator=(const HashTable& b);

		void clear();
		bool erase(const String& key);
		bool insert(const String& key, const Value& value);
		bool contains(const String& key) const;

		Value& operator[](const String& key);

		Value& at(const String& key);
		const Value& at(const String& key) const;

		size_t size() const; // returns memory size of HasshTable
		bool empty() const; // is_empty!!!

		friend bool operator==(const HashTable& a, const HashTable& b);
		friend bool operator!=(const HashTable& a, const HashTable& b);
};

bool operator==(const HashTable& a, const HashTable& b);
bool operator!=(const HashTable& a, const HashTable& b);

unsigned int hash(String key);

#endif
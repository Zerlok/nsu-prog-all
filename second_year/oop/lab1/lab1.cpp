#include "table.h"

unsigned int hash(String key)
{
	return key.size() * key[0];
}

HashTable& HashTable::operator=(const HashTable& b)
{
	data_end = b.data_end;

	try
	{
		data = (Value*)realloc(data, data_end);
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}

	for (int i = 0; i < data_end; i++)
	{
		data[i] = b.data[i];
	}
}


Value& HashTable::operator[](const String& key)
{
	unsigned int h = hash(key);
	unsigned int index = h % data_end;
	Value *last_data = &data[index], *curr_data = &data[index];

	// std::cout << h << ", " << data_end << ", " << index << std::endl;

	/* Cell is not empty */
	while (curr_data == NULL)
	{
		if (curr_data->name == key) // Can I compare strings?
		{
			return *curr_data;
		}
		last_data = curr_data;
		curr_data = last_data->next;
	}

	// std::cout << "After cycle" << std::endl;

	/* If empty cell or key not found -> create a new value */
	Value *new_value = new Value;

	new_value->name = key;
	new_value->next = NULL;
	new_value->age = 18;
	new_value->course = 1;
	new_value->average_mark = 4;
	new_value->department = "Information Technology";

	// std::cout << "After new value creation" << std::endl;

	// std::cout << last_data << std::endl;

	last_data->next = new_value;

	// std::cout << "At value returning" << std::endl;

	return *new_value;
}


// Constructor
HashTable::HashTable()
{
	data_end = 1000;

	try
	{
		data = new Value[data_end];
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}
}


// Destructor
HashTable::~HashTable()
{
	// std::cout << "Gonna destroy the table... ";
	delete[] data;
	// std::cout << "done" << std::endl;
}


HashTable::HashTable(const HashTable& b)
{
	data_end = b.data_end;

	try
	{
		data = new Value[data_end];
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}

	for (int i = 0; i < data_end; i++)
	{
		data[i] = b.data[i];
	}
}


/* Will it work, if these fields are private? */
void HashTable::swap(HashTable& b)
{
	unsigned int tmp_data_end = data_end;
	Value *tmp_data = data;

	data_end = b.data_end;
	data = b.data;

	b.data_end = tmp_data_end;
	b.data = tmp_data;	
}


int main(int argc, char **argv)
{
	HashTable ht;

	if (argc > 1)
	{
		for (int i = 1; i < argc; i++)
		{
			std::cout << i << " : " << ht[argv[i]].name << std::endl;
		}

		std::cout << "At [1] : " << ht[argv[1]].name << std::endl;
	}

	return 0;
}
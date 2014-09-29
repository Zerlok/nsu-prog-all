#include "table.h"
#include <iostream>


/* -------------- ACCESSORY FUNCTIONS -------------- */

/* 
	DO NOT CHANGE IT! (while DEBUG it's necessaty for collisions test).
	For example: "Danil" and "Diman" have the same hash.
*/
unsigned int hash(const String& key)
{
	return key.size() * key[0];
}


/*
	Gets key and calculates a big hash number.
*/
int good_hash(const String& key)
{
	int sum, h = 1;
	int len = key.size();

	for (int max_i = 0; max_i < len; max_i++)
	{
		sum = max_i * len;

		for (int i = 0; i < max_i; i++)
		{
			sum += key[i];
		}

		h *= sum;
	}

	return len * h;
}


/* -------------- STUDENT METHODS -------------- */

/*
	Creates new Value object.
*/
Value::Value(const String& name, const unsigned int age,
	const unsigned int course, const String& department)
{
	_name = name;
	_age = age;
	_course = course;
	_department = department;
}


Value::~Value()
{
	if (DEBUG_SUPER) std::cout << "Destoying the Value "
								<< as_string()
								<< "... done" << std::endl;
}


/*
	Copy the Value object from given Value object.
*/
Value::Value(const Value& value)
{
	_name = value._name;
	_age = value._age;
	_course = value._course;
	_department = value._department;
}


/*
	Checks the equal between two Value objects.
	Returns: is all fields are equal in both Value objects.
*/
bool operator==(const Value& value1, const Value& value2)
{
	return (
			value1._name == value2._name &&
			value1._age == value2._age &&
			value1._course == value2._course &&
			value1._department == value2._department
	);
}


/*
	Checks the difference between two Value objects.
	Returns: is not equal objects.
*/
bool operator!=(const Value& value1, const Value& value2)
{
	return !(value1 == value2);
}


/*
	Converts Value fields to string.
	Returns: string about Value object.
	For student example: "<name>:(<age>,<course>,<average_mark>,<department>)".
*/
String Value::as_string() const
{
	std::stringstream str_stream;
	
	str_stream << _name << ":("
				<< _age << ","
				<< _course << ","
				<< _department << ")";

	return str_stream.str();
}


/* -------------- ITEM METHODS -------------- */

/*
	Creates an Item object with specified Value object.
	Key generates from Value (for example the student name is a key).
*/
Item::Item(const Value& value)
{
	_key = value.get_name();
	_value = new Value(value);
	_next = NULL;
}


/*
	Creates an Item object with specified key and Value object.
*/
Item::Item(const String& key, const Value& value)
{
	_key = key;
	_value = new Value(value);
	_next = NULL;
}


Item::~Item()
{
	if (DEBUG_SUPER) std::cout << "Destoying the Item "
								<< as_string() << "... ";

	delete _value;
	delete _next;

	if (DEBUG_SUPER) std::cout << "done" << std::endl;
}


/*
	Copy Item object from given Item object.
*/
Item::Item(const Item& item)
{
	Value value = item.get_value();

	_key = item._key;
	_value = new Value(item.get_value());
	push_back(item.get_next());
}


bool Item::is_key_equals(const String& key) const
{
	return (_key == key);
}


bool Item::is_key_not_equals(const String& key) const
{
	return (_key != key);
}


/*
	Returns: the pointer to the next Value object in list of Value objects.
*/
Item *Item::get_next() const
{
	return _next;
}


/*
	Returns: Value object from Item object field.
	If Item object is empty, raises an exception.
*/
Value& Item::get_value()
{
	if (_value == NULL)
	{
		throw std::invalid_argument(ERR_NO_VALUE_IN_ITEM);
	}

	return *(_value);
}


const Value& Item::get_value() const
{
	if (_value == NULL)
	{
		throw std::invalid_argument(ERR_NO_VALUE_IN_ITEM);
	}

	return *(_value);
}


/*
	Checks is two Item object are equal.
	Returns: is keys are equal.
*/
bool operator==(const Item& item1, const Item& item2)
{
	return (item1._key == item2._key && *(item1._value) == *(item2._value));
}


/*
	Checks is two Item objects are NOT equal.
	Returns: is keys are NOT equal.
*/
bool operator!=(const Item& item1, const Item& item2)
{
	return !(item1 == item2);
}


/*
	Pushes back an Item object to the list of Item objects.
	Fails if current Item object and any Item object
	from given Item objects list are equal.
*/
// TODO: Rewrite the function description.
bool Item::push_back(Item *item)
{
	Item *p_item = item;

	if (item == NULL)
	{
		_next = NULL;

		return true;
	}

	while (p_item != NULL)
	{
		if (p_item->is_key_equals(_key))
		{
			return false;
		}

		p_item = p_item->get_next();
	}

	_next = new Item(*item);

	return true;
}


/*
	Do the same as a method above, if input is a reference to Item object.
*/
bool Item::push_back(Item& item)
{
	return push_back(&item);
}


/*
	Converts Item fields to string.
	Returns: string about Item object.
	"<key>:[<value>,<next (key)>]".
*/
String Item::as_string() const
{
	std::stringstream str_stream;
	
	str_stream << _key << ":[";
	
	if (_value == NULL)
	{
		str_stream << "NULL";
	}
	else
	{
		str_stream << _value->as_string();
	}

	str_stream << ",";

	if (_next == NULL)
	{
		str_stream << "NULL";
	}
	else
	{
		str_stream << _next->as_string();
	}

	str_stream << "]";

	return str_stream.str();
}


/* -------------- HASHTABLE METHODS -------------- */

HashTable::HashTable(int mem)
{
	_data_end = mem;

	try
	{
		_data = new Item*[mem];
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}

	for (int i = 0; i < _data_end; i++)
	{
		_data[i] = NULL;
	}
}


HashTable::~HashTable()
{
	if (DEBUG_SUPER) std::cout << "Destroying the HashTable... ";
	
	delete[] _data;

	if (DEBUG_SUPER) std::cout << "done" << std::endl;
}


HashTable::HashTable(const HashTable& hashtable)
{
	_data_end = hashtable._data_end;

	try
	{
		_data = new Item*[_data_end];
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}

	for (int i = 0; i < _data_end; i++)
	{
		if (hashtable._data[i] != NULL)
		{
			_data[i] = new Item(*(hashtable._data[i]));
		}
		else
		{
			_data[i] = NULL;
		}
	}
}


Value& HashTable::get(const String& key)
{
	Item *curr_item = _data[_get_index(key)];

	while (curr_item != NULL && curr_item->is_key_not_equals(key))
	{
		curr_item = curr_item->get_next();
	}

	if (curr_item == NULL)
	{
		throw std::invalid_argument(ERR_KEY_NOT_FOUND);
	}

	return curr_item->get_value();
}


const Value& HashTable::get(const String& key) const
{
	Item *curr_item = _data[_get_index(key)];

	while (curr_item != NULL && curr_item->is_key_not_equals(key))
	{
		curr_item = curr_item->get_next();
	}
	
	if (curr_item == NULL)
	{
		throw std::invalid_argument(ERR_KEY_NOT_FOUND);
	}

	return curr_item->get_value();
}


size_t HashTable::get_size() const
{
	size_t items_num = 0;
	Item *curr_item;

	for (int i = 0; i < _data_end; i++)
	{
		curr_item = _data[i];

		while (curr_item != NULL)
		{
			items_num++;
			curr_item = curr_item->get_next();
		}
	}

	return items_num;
}


bool HashTable::is_empty() const
{
	std::cout << "trying to find out is this hashtable an empty...";
	for (int i = 0; i < _data_end; i++)
	{
		if (_data[i] != NULL)
		{
			std::cout << _data[i]->as_string() << std::endl;
			return false;
		}
	}

	std::cout << "seems like it is.";

	return true;
}


Value& HashTable::operator[](const String& key)
{
	Value *value = new Value(key), *inner_value = _search(key);
	
	if (inner_value == NULL)
	{
		insert(key, *value);

		return *value;
	}
	else
	{
		delete value;

		return *inner_value;
	}
}


HashTable& HashTable::operator=(const HashTable& hashtable)
{
//	clear();

//	_data_end = hashtable._data_end;
	
//	try
//	{
//		_data = new Item*[_data_end];
//	}
//	catch (std::bad_alloc)
//	{
//		std::cout << ERR_BAD_ALLOC << std::endl;
//	}


//	for (int i = 0; i < _data_end; i++)
//	{
//		_data[i] = hashtable._data[i];
//	}

	static HashTable new_table(hashtable);

	return new_table;
}


bool operator==(const HashTable& hashtable1, const HashTable& hashtable2)
{
	if (hashtable1._data_end == hashtable2._data_end)
	{
		Item *a_item, *b_item;

		for (int i = 0; i < hashtable1._data_end; i++)
		{
			a_item = hashtable1._data[i];
			b_item = hashtable2._data[i];

			while (a_item != NULL && b_item != NULL)
			{
				// if (a_item->get_key() != b_item->get_key() ||
				// 	a_item->get_value() != b_item->get_value())
				if (*a_item != *b_item)
				{
					return false;
				}

				a_item = a_item->get_next();
				b_item = b_item->get_next();
			}

			if ((a_item == NULL && b_item != NULL) ||
				(a_item != NULL && b_item == NULL))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}


bool operator!=(const HashTable& hashtable1, const HashTable& hashtable2)
{
	return !(hashtable1 == hashtable2);
}


void HashTable::swap(HashTable& hashtable)
{
	unsigned int tmp_data_end = _data_end;
	Item **tmp_data = _data;

	_data_end = hashtable._data_end;
	_data = hashtable._data;

	hashtable._data_end = tmp_data_end;
	hashtable._data = tmp_data;	
}


void HashTable::clear()
{
	// Raises the segmentation fault if uncommented!
//	delete[] _data;
}


bool HashTable::erase(const String& key)
{
	std::cout << "start erasing at " << key << "..." << std::endl;

	int i = _get_index(key);
	Item *last_item = _data[i], *curr_item = _data[i], *next_item = _data[i];

	std::cout << hash(key) << " | "<< i << std::endl;

	if (last_item == NULL)
	{
		return false;
	}

	std::cout << "Not empty cell" << std::endl;
	std::cout << _data[i]->as_string() << std::endl;

	if (last_item->is_key_equals(key))
	{
		next_item = last_item->get_next();

		if (next_item == NULL)
		{
			_data[i] = NULL;
		}
		else
		{
			_data[i] = new Item(*next_item);
			delete last_item;
		}

		return true;
	}

	std::cout << "Not first key" << std::endl;

	while (curr_item != NULL)
	{
		if (curr_item->is_key_equals(key))
		{
			last_item->push_back(next_item);
			delete curr_item;
			
			return true;
		}

		last_item = curr_item;
		curr_item = curr_item->get_next();
	}

	std::cout << ERR_KEY_NOT_FOUND << std::endl;

	return false;
}


bool HashTable::insert(const String& key, const Value& value)
{
	std::cout << "start inserting" << std::endl;

	int i = _get_index(key);
	Item *last_item, *curr_item = _data[i];

	std::cout << hash(key) << " | "<< i << std::endl;

	if (curr_item == NULL)
	{
		_data[i] = new Item(key, value);
		return true;
	}

	std::cout << "the same index " << curr_item->as_string() << std::endl;
	std::cout << "inserting... " << value.as_string() << std::endl;

	while (curr_item != NULL)
	{
		if (curr_item->is_key_equals(key))
		{
			return false;
		}

		last_item = curr_item;
		curr_item = curr_item->get_next();
	}

	std::cout << key << " " << ERR_KEY_NOT_FOUND << std::endl;

	static Item *new_item = new Item(key, value);

	std::cout << new_item->as_string() << std::endl;

	last_item->push_back(new_item);

	std::cout << "pushed back." << std::endl;

	return true;
}


bool HashTable::is_contains(const String& key) const
{
	if (_search(key) == NULL) return false;
	return true;
}


int HashTable::_get_index(const String& key) const
{
	return (DEBUG) ? (hash(key) % _data_end) : (good_hash(key) % _data_end);
}


Value *HashTable::_search(const String& key) const
{
	int i = _get_index(key);
	Item *curr_item = _data[i];

	while (curr_item != NULL)
	{
		if (curr_item->is_key_equals(key))
		{
			return &(curr_item->get_value());
		}

		curr_item = curr_item->get_next();
	}

	return NULL;
}

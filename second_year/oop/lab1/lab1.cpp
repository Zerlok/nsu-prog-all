#include "table.h"
#include <iostream>


/* -------------- ACCESSORY FUNCTIONS -------------- */

#ifndef __HTABLE_DEBUG__

/*
	Calculates a big hash number for the specified key.
*/
int hash(const String& key)
{
	int sum, h = 1;
	int len = key.size();

	for (int max_i = 0; max_i < len; max_i++)
	{
		sum = max_i * len;

		for (int i = 0; i < max_i; i++)
		{
			sum += key[i] + i * (MEM_INIT % 10);
		}

		sum += max_i * (MEM_INIT % 100);

		h *= sum;
	}

	h += (h % MEM_INIT);

	return (h > 0) ? h : -h;
}

#else

/* 
	DO NOT CHANGE IT!
	HashTable class uses this function while DEBUG is defined.
	For example: "Danil" and "Diman" have the same hash.
*/
int hash(const String& key)
{
	return key.size() * key[0];
}

#endif


/* -------------- STUDENT METHODS -------------- */

Value::Value(const String& name, const unsigned int age,
	const unsigned int course, const String& department)
{
	_name = name;
	_age = age;
	_course = course;
	_department = department;
}


Value::~Value() {}


/*
	Makes a copy of given Value object.
*/
Value::Value(const Value& value)
{
	_name = value._name;
	_age = value._age;
	_course = value._course;
	_department = value._department;
}


/*
	Copies all fields from given Value object to the current Value object.
*/
Value& Value::operator=(const Value& value)
{
	_name = value._name;
	_age = value._age;
	_course = value._course;
	_department = value._department;
}


/*
	Checks are two Value objects same.
	Returns: is all fields are same in both Value objects.
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
	Checks are Value objects different.
	Returns: is NOT equal objects.
*/
bool operator!=(const Value& value1, const Value& value2)
{
	return !(value1 == value2);
}


/*
	Returns the value from _name field of current Value object.
*/
const String& Value::return_name() const
{
	return _name;
}


/* -------------- ITEM METHODS -------------- */

/*
	Creates an Item object with specified Value object.
	Key generates from Value (for example the student name is a key).
*/
// Item::Item(const Value& value)
// {
// 	_key = value.return_name();
// 	_value = new Value(value);
// 	_next = NULL;
// }


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
	delete _value;
}


/*
	Makes a copy of given Item object.
*/
Item::Item(const Item& item)
{
	Value value = item.return_value();

	_key = item._key;
	_value = new Value(item.return_value());
	push_back(item.get_next());
}


/*
	Checks are specified key and Item object key same.
*/
bool Item::is_key_equals(const String& key) const
{
	return (_key == key);
}


/*
	Checks are specified key and Item object key NOT same.
*/
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
	Returns: the current Item object key.
*/
String Item::return_key()
{
	return _key;
}


/*
	Returns: the current Item object key.
*/
const String Item::return_key() const
{
	return _key;
}


/*
	Returns: Value object from Item object.
	If Item object is empty, raises an exception.
*/
Value& Item::return_value()
{
	if (_value == NULL)
	{
		throw std::invalid_argument(ERR_NO_VALUE_IN_ITEM);
	}

	return *(_value);
}


/*
	Returns: Value object from Item object.
	If Item object is empty, raises an invalid argument exception.
*/
const Value& Item::return_value() const
{
	if (_value == NULL)
	{
		throw std::invalid_argument(ERR_NO_VALUE_IN_ITEM);
	}

	return *(_value);
}


/*
	Checks are two Item object same.
	Returns: are keys and values equal.
*/
bool operator==(const Item& item1, const Item& item2)
{
	return (item1._key == item2._key && *(item1._value) == *(item2._value));
}


/*
	Checks are two Item objects NOT same.
	Returns: are objects NOT equal.
*/
bool operator!=(const Item& item1, const Item& item2)
{
	return !(item1 == item2);
}


/*
	Pushes back an Item object to the list of current Item objects.
	Fails if any Item object from given Item objects list are equal to the key of the current Item object (when trying to create a cycled list).
*/
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


/* -------------- HASHTABLE METHODS -------------- */

HashTable::HashTable(int mem)
{
	if (mem < 1)
	{
		throw std::invalid_argument(ERR_BAD_HTABLE_SIZE);
	}

	_cells_num = mem;

	try
	{
		_data = new Item*[mem];
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}

	for (int i = 0; i < _cells_num; i++)
	{
		_data[i] = NULL;
	}
}


HashTable::~HashTable()
{
	clear();
	delete[] *_data;
}


/*
	Makes a copy of given HashTable object.
*/
HashTable::HashTable(const HashTable& hashtable)
{
	_cells_num = hashtable._cells_num;

	try
	{
		_data = new Item*[_cells_num];
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}

	for (int i = 0; i < _cells_num; i++)
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


/*
	Returns: the Value from given key from current HashTable object.
*/
Value& HashTable::get(const String& key)
{
	Value *requested_value = _search(key);

	if (requested_value == NULL) throw std::invalid_argument(ERR_KEY_NOT_FOUND);

	return *requested_value;
}


/*
	Returns: the Value from given key from current HashTable object.
*/
const Value& HashTable::get(const String& key) const
{
	return get(key);
}


/*
	Calculates and returns how many Item objects are in the current HashTable object.
*/
size_t HashTable::get_size() const
{
	size_t items_num = 0;
	Item *curr_item;

	for (int i = 0; i < _cells_num; i++)
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


/*
	Checks is the current HashTable object empty.
*/
bool HashTable::is_empty() const
{
	for (int i = 0; i < _cells_num; i++)
	{
		if (_data[i] != NULL) return false;
	}

	return true;
}


/*
	Returns: the Value object from specified key from current HashTable object.
	If Value does not exist - inserts the new Value object into HashTable and returns it.
*/
Value& HashTable::operator[](const String& key)
{
	Value *inner_value = _search(key);
	
	if (inner_value == NULL)
	{
		Value value(key);

		insert(key, value);

		return *_search(key);
	}

	return *inner_value;
}


/*
	Copies all fields from specified HashTable object to the current HashTable object.
*/
HashTable& HashTable::operator=(const HashTable& hashtable)
{
	clear();

	_cells_num = hashtable._cells_num;
	
	try
	{
		delete[] *_data; // TODO: Ask about that.
		_data = new Item*[_cells_num];
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}


	for (int i = 0; i < _cells_num; i++)
	{
		if (hashtable._data[i] == NULL)
		{
			_data[i] = NULL;
		}
		else
		{
			_data[i] = new Item(*(hashtable._data[i]));
		}
	}
}


/*
	Checks are two HashTable objects same.
	Returns: false if HashTable sizes are different or any inner Item object are not same, otherwise returns true.
*/
bool operator==(const HashTable& hashtable1, const HashTable& hashtable2)
{
	if (hashtable1._cells_num == hashtable2._cells_num)
	{
		Item *a_item, *b_item;

		for (int i = 0; i < hashtable1._cells_num; i++)
		{
			a_item = hashtable1._data[i];
			b_item = hashtable2._data[i];

			while (a_item != NULL && b_item != NULL)
			{
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


/*
	Checks are two HashTable objects NOT same.
	Returns: are HashTable objects NOT equal.
*/
bool operator!=(const HashTable& hashtable1, const HashTable& hashtable2)
{
	return !(hashtable1 == hashtable2);
}


/*
	Changes fields between current and specified HashTable objects.
*/
void HashTable::swap(HashTable& hashtable)
{
	unsigned int tmp_cells_num = _cells_num;
	Item **tmp_data = _data;

	_cells_num = hashtable._cells_num;
	_data = hashtable._data;

	hashtable._cells_num = tmp_cells_num;
	hashtable._data = tmp_data;	
}


/*
	Erases all data from current HashTable object.
*/
void HashTable::clear()
{
	for (int i = 0; i < _cells_num; i++)
	{
		Item *tmp = _data[i];

		while (tmp) {
			Item *delete_item = tmp;
			tmp = tmp->get_next();
			delete delete_item;
		}

		_data[i] = NULL;
	}
}


/*
	Erases value with specified key from current HashTable object and returns true.
	Otherwise returns false, if the value with specified key does not exist in HashTable object.
*/
bool HashTable::erase(const String& key)
{
	int i = _get_index(key);
	Item *last_item = _data[i], *curr_item = _data[i], *next_item = _data[i];

	if (last_item == NULL)
	{
		return false;
	}

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

	while (curr_item != NULL)
	{
		if (curr_item->is_key_equals(key))
		{
			last_item->push_back(curr_item->get_next());
			delete curr_item;
			
			return true;
		}

		last_item = curr_item;
		curr_item = curr_item->get_next();
	}

	return false;
}


/*
	Inserts the Value object with specified key into the current HashTable object and returns true if successfull.
	Otherwise returns false, if Item object with the same key already exists in the HashTable object.
*/
bool HashTable::insert(const String& key, const Value& value)
{
	_check_and_expand();

	int i = _get_index(key);
	Item *last_item, *curr_item = _data[i];

	if (curr_item == NULL)
	{
		_data[i] = new Item(key, value);

		return true;
	}

	while (curr_item != NULL)
	{
		if (curr_item->is_key_equals(key)) return false;

		last_item = curr_item;
		curr_item = curr_item->get_next();
	}

	Item *new_item = new Item(key, value);
	last_item->push_back(new_item);

	return true;
}


/*
	Checks does the value with specified key exist in the HashTable object.
	Returns: true if it does, false - if not.
*/
bool HashTable::is_contains(const String& key) const
{
	return (_search(key) != NULL);
}


/*
	Private method!
	Calculates the index of specified key in HashTable object and returns it.
*/
int HashTable::_get_index(const String& key) const
{
	if (_cells_num < 1)
	{
		throw std::invalid_argument(ERR_BAD_HTABLE_SIZE);
	}

	return hash(key) % _cells_num;
}


/*
	Private method!
	Looks for the value with specified key in Hashtable object.
	Returns: pointer to the value if exists, otherwise - NULL.
*/
Value *HashTable::_search(const String& key) const
{
	int i = _get_index(key);
	Item *curr_item = _data[i];

	while (curr_item != NULL)
	{
		if (curr_item->is_key_equals(key))
		{
			return &(curr_item->return_value());
		}

		curr_item = curr_item->get_next();
	}

	return NULL;
}


/*
	Private method!
	Checks the HashTable object for fullness.
	If there are a lot of objects, expands this HashTable object.
*/
bool HashTable::_check_and_expand()
{
	if (get_size() * FULLNESS_FACTOR < _cells_num)
	{
		return false;
	}

	HashTable tmp_table(_cells_num * FULLNESS_FACTOR);
	Item *curr_item;

	for (int i = 0; i < _cells_num; i++)
	{
		curr_item = _data[i];

		while (curr_item != NULL)
		{
			tmp_table.insert(
					curr_item->return_key(),
					curr_item->return_value()
			);

			curr_item = curr_item->get_next();
		}
	}

	*this = tmp_table;

	return true;
}

#include "table.h"
#include <iostream>


/* -------------- ACCESSORY FUNCTIONS -------------- */

#ifdef __HTABLE_DEBUG__

/* 
	DO NOT CHANGE IT! (while DEBUG it's necessaty for collisions test).
	For example: "Danil" and "Diman" have the same hash.
*/
int hash(const String& key)
{
	return key.size() * key[0];
}

#else

/*
	Gets key and calculates a big hash number.
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
			sum += key[i];
		}

		h *= (sum + 997);
	}

	// Abs?
	return (h > 0) ? h : -h;
}

#endif


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


Value::~Value() {}


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
	===May be not necessary operator!===
	Copy the Value object from given Value object.
*/
Value& Value::operator=(const Value& value)
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
	_key = value.return_name();
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
	delete _value;
	delete _next;
}


/*
	Copy Item object from given Item object.
*/
Item::Item(const Item& item)
{
	Value value = item.return_value();

	_key = item._key;
	_value = new Value(item.return_value());
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


String Item::return_key()
{
	return _key;
}


const String Item::return_key() const
{
	return _key;
}


/*
	Returns: Value object from Item object field.
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


const Value& Item::return_value() const
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



// 	Do the same as a method above, if input is a reference to Item object.

// bool Item::push_back(Item& item)
// {
// 	return push_back(&item);
// }


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
	if (mem < 1)
	{
		throw std::invalid_argument(ERR_BAD_HTABLE_SIZE);
	}

	_critical_items_num = _cells_num = mem;

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


HashTable::HashTable(const HashTable& hashtable)
{
	_critical_items_num = _cells_num = hashtable._cells_num;

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


Value& HashTable::get(const String& key)
{
	Value *requested_value = _search(key);

	if (requested_value == NULL) throw std::invalid_argument(ERR_KEY_NOT_FOUND);

	return *requested_value;
}


const Value& HashTable::get(const String& key) const
{
	return get(key);
}


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


bool HashTable::is_empty() const
{
	for (int i = 0; i < _cells_num; i++)
	{
		if (_data[i] != NULL) return false;
	}

	return true;
}


Value& HashTable::operator[](const String& key)
{
	Value *inner_value = _search(key);
	
	if (inner_value == NULL)
	{
		Value *value = new Value(key);

		insert(key, *value);

		return *value;
	}

	return *inner_value;
}


HashTable& HashTable::operator=(const HashTable& hashtable)
{
	clear();

	_critical_items_num = _cells_num = hashtable._cells_num;
	
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


bool operator!=(const HashTable& hashtable1, const HashTable& hashtable2)
{
	return !(hashtable1 == hashtable2);
}


void HashTable::swap(HashTable& hashtable)
{
	unsigned int tmp_cells_num = _cells_num;
	Item **tmp_data = _data;

	_cells_num = hashtable._cells_num;
	_data = hashtable._data;

	hashtable._cells_num = tmp_cells_num;
	hashtable._data = tmp_data;	
}


void HashTable::clear()
{
	for (int i = 0; i < _cells_num; i++)
	{
		delete _data[i];
		_data[i] = NULL;
	}
}


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


bool HashTable::is_contains(const String& key) const
{
	return (_search(key) != NULL);
}


int HashTable::_get_index(const String& key) const
{
	if (_cells_num < 1)
	{
		throw std::invalid_argument(ERR_BAD_HTABLE_SIZE);
	}

	return hash(key) % _cells_num;
}


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


bool HashTable::_check_and_expand()
{
	if (get_size() < _critical_items_num)
	{
		return false;
	}

	HashTable tmp_table(_cells_num * 2);
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

#include "htable.h"


/*
 *	-------------- HASHTABLE METHODS --------------
 */
HashTable::HashTable(int mem)
{
	if (mem < 1)
	{
		throw std::invalid_argument(ERR_BAD_HTABLE_SIZE);
	}

	_items_num = 0;
	_cells_num = mem;
	_data = new Item*[mem];

	std::fill(_data, _data + _cells_num, static_cast<Item *>(NULL));
}


/*
 *	Hashtable destructor doesn't use the clear function,
 *	because clear deletes, then allocates new memory for _data
 *	and fills NULLs into each _data pointer - it takes a time.
 *	But when hashtable object destroying, it will never be used again,
 *	that's why it's better use only 'delete[] _data;' without clear.
 */
HashTable::~HashTable()
{
	_remove_data();
}


/*
 *	Makes a copy of given HashTable object.
 */
HashTable::HashTable(const HashTable& hashtable)
{
	_items_num = hashtable._items_num;
	_cells_num = hashtable._cells_num;
	_data = new Item*[_cells_num];

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
 *	Returns: the Value object from specified key from current HashTable object.
 *	If Value does not exist - inserts the new Value object into HashTable and returns it.
 */
Value& HashTable::operator[](const String& key)
{
	Value *inner_value = _search(key);
	
	if (inner_value == NULL)
	{
		Value value(key);

		insert(key, value);

		return (*_search(key));
	}

	return (*inner_value);
}


/*
 *	Copies all fields from specified HashTable object to the current HashTable object.
 */
HashTable& HashTable::operator=(const HashTable& hashtable)
{
	if (this == (&hashtable))
		return (*this);

	_remove_data();

	_cells_num = hashtable._cells_num;
	_data = new Item*[_cells_num];

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

	_items_num = hashtable._items_num;

	return (*this);
}


/*
 *	Checks are two HashTable objects same.
 *	Returns: false if HashTable sizes are different or any inner Item object are not same,
 *	otherwise returns true.
 */
bool operator==(const HashTable& hashtable1, const HashTable& hashtable2)
{
	if ((hashtable1._cells_num == hashtable2._cells_num)
		&& (hashtable1._items_num == hashtable2._items_num))
	{
		Item *a_item, *b_item;

		for (int i = 0; i < hashtable1._cells_num; i++)
		{
			a_item = hashtable1._data[i];
			b_item = hashtable2._data[i];

			while ((a_item != NULL) && (b_item != NULL))
			{
				if ((*a_item) != (*b_item))
				{
					return false;
				}

				a_item = a_item->get_next();
				b_item = b_item->get_next();
			}

			if (((a_item == NULL) && (b_item != NULL))
				|| ((a_item != NULL) && (b_item == NULL)))
			{
				return false;
			}
		}

		return true;
	}

	return false;
}


/*
 *	Checks are two HashTable objects NOT same.
 *	Returns: are HashTable objects NOT equal.
 */
bool operator!=(const HashTable& hashtable1, const HashTable& hashtable2)
{
	return !(hashtable1 == hashtable2);
}


/*
 *	Cleans all data from current HashTable object.
 *	Deletes _data's pointers, allocates new memory
 *	and fills NULLs into each _data's pointer.
 */
void HashTable::clear()
{
	_remove_data();

	_data = new Item*[_cells_num];
	std::fill(_data, _data + _cells_num, static_cast<Item *>(NULL));
}


/*
 *	Erases value with specified key from current HashTable object and returns true.
 *	Otherwise returns false, if the value with specified key does not exist in HashTable object.
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
		_items_num--;
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
			_items_num--;
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
 *	Returns: the Value from given key from current HashTable object.
 */
Value& HashTable::get(const String& key)
{
	Value *requested_value = _search(key);

	if (requested_value == NULL)
		throw std::invalid_argument(ERR_KEY_NOT_FOUND);

	return *requested_value;
}


/*
 *	Returns: the constant Value from given key from current HashTable object.
 */
const Value& HashTable::get(const String& key) const
{
	Value *requested_value = _search(key);

	if (requested_value == NULL)
		throw std::invalid_argument(ERR_KEY_NOT_FOUND);

	return *requested_value;
}


/*
 *	Calculates and returns how many Item objects are in the current HashTable object.
 */
size_t HashTable::get_size() const
{
	return _items_num;
}


/*
 *	Inserts the Value object with specified key into the current HashTable object
 *	and returns true if successfull. Otherwise returns false, if Item object
 *	with the same key already exists in the HashTable object.
 */
bool HashTable::insert(const String& key, const Value& value)
{
	_check_and_expand();

	int i = _get_index(key);
	Item *last_item, *curr_item = _data[i];

	if (curr_item == NULL)
	{
		_items_num++;
		_data[i] = new Item(key, value);

		return true;
	}

	while (curr_item != NULL)
	{
		if (curr_item->is_key_equals(key)) return false;

		last_item = curr_item;
		curr_item = curr_item->get_next();
	}

	_items_num++;
	Item *new_item = new Item(key, value);
	last_item->push_back(new_item);

	return true;
}


/*
 *	Checks does the value with specified key exist in the HashTable object.
 *	Returns: true if it does, false - if not.
 */
bool HashTable::is_contains(const String& key) const
{
	return (_search(key) != NULL);
}


/*
 *	Checks is the current HashTable object empty.
 */
bool HashTable::is_empty() const
{
	return !(_items_num);
}


/*
 *	Changes fields between two HashTable objects.
 */
void swap_ht(HashTable& a, HashTable& b)
{
	std::swap(a._items_num, b._items_num);
	std::swap(a._cells_num, b._cells_num);
	std::swap(a._data, b._data);
}


/*
 *	Private method!
 *	Checks the HashTable object for fullness.
 *	If there are a lot of objects, expands this HashTable object.
 */
bool HashTable::_check_and_expand()
{
	if (_items_num * FULLNESS_FACTOR < _cells_num)
	{
		return false;
	}

	/*
	 *	Table has got a lot of items ->
	 *	Have to create a bigger table, to copy all data into it.
	 *	Then swap them.
	 */
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

	swap_ht((*this), tmp_table);
	return true;
}


/*
 *	Private method!
 *	Calculates the index of specified key in HashTable object and returns it.
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
 *	Private method!
 *	Looks for the value with specified key in Hashtable object.
 *	Returns: pointer to the value if exists, otherwise - NULL.
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
 *	Private method!
 *	Remove all pointers from _data.
 */
void HashTable::_remove_data()
{
	_items_num = 0;

	for (int i = 0; i < _cells_num; i++)
	{
		delete _data[i];
	}

	delete[] _data;
}


/*
 *	-------------- ACCESSORY FUNCTIONS --------------
 */
#ifndef __HTABLE_DEBUG__

/*
 *	Calculates a big hash number for the specified key.
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
 *	DO NOT CHANGE IT!
 *	HashTable class uses this function while DEBUG is defined.
 *	For example: "Danil" and "Diman" have the same hash.
 */
int hash(const String& key)
{
	return key.size() * key[0];
}

#endif

#include "table.h"


/* -------------- ACCESSORY FUNCTIONS -------------- */

/* DO NOT CHANGE IT! (while DEBUG it's necessaty for collisions test) */
unsigned int hash(const String& key)
{
	return key.size() * key[0];
}


/* -------------- STUDENT METHODS -------------- */

Value::Value(const String& _name, const unsigned int _age,
	const unsigned int _course, const float _average_mark,
	const String& _department)
{
	this->name = _name;
	this->age = _age;
	this->course = _course;
	this->average_mark = _average_mark;
	this->department = _department;
}


Value::~Value() {}


Value::Value(const Value& s)
{
	this->name = s.name;
	this->age = s.age;
	this->course = s.course;
	this->average_mark = s.average_mark;
	this->department = s.department;
}


Value& Value::operator=(const Value& s)
{
	this->name = s.name;
	this->age = s.age;
	this->course = s.course;
	this->average_mark = s.average_mark;
	this->department = s.department;
}


bool operator==(const Value& a, const Value& b)
{
	return (a.name == b.name && a.age == b.age && a.course == b.course &&
		a.average_mark == b.average_mark && a.department == b.department);
}


bool operator!=(const Value& a, const Value& b)
{
	return !(a == b);
}


/* -------------- ITEM METHODS -------------- */

Item::Item(const String& _key)
{
	this->key = _key;
	this->value = NULL;
	this->next = NULL;
}


Item::Item(const Value& _value)
{
	this->key = _value.get_name();
	this->value = const_cast<Value*>(&_value);
	this->next = NULL;
}


Item::Item(const String& _key, const Value& _value)
{
	this->key = _key;
	this->value = const_cast<Value*>(&_value);
	this->next = NULL;
}


// TODO: Ask about delete
Item::~Item()
{
	// std::cout << "Destoying the Item... ";

	// if (value) delete value;
	// std::cout << "... ";

	// if (next) delete next;
	/* When next not null, raises "double free corruption" */

	// std::cout << "done" << std::endl;
}
 

Item::Item(const Item& i)
{
	this->key = i.key;
	this->value = new Value(*(i.value));
	this->next = i.next;
}


Value& Item::get_value()
{
	if (value == NULL)
	{
		throw std::exception();
	}

	return *(value);
}


Item *Item::get_next() const
{
	return next;
}


void Item::set_next(Item *i)
{
	this->next = i;
}


Item& Item::operator=(const Item& i)
{
	this->key = i.key;
	this->value = i.value;
	this->next = i.next;
}

bool operator==(const Item& a, const Item& b)
{
	return (a.key == b.key);
}


bool operator!=(const Item& a, const Item& b)
{
	return (a.key != b.key);
}


bool Item::push_back(Item& i)
{
	if (this->key == i.key)
	{
		return false;
	}

	this->next = &(i);
	return true;
}


bool Item::is_empty() const
{
	return (value == NULL);
}


bool Item::push_node(Item& i)
{
	Item *own_item = this, *curr_item = i.get_next();

	while (own_item->next != NULL)
	{
		own_item = own_item->next;
	}

	while (curr_item != NULL)
	{
		own_item->next = new Item(curr_item->get_value());
		curr_item = curr_item->get_next();
	}

	own_item->next = NULL;

	return true;
}


/* -------------- HASHTABLE METHODS -------------- */

HashTable::HashTable(int _mem)
{
	data_end = _mem;

	try
	{
		data = new Item*[data_end];
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}

	clear();
}


HashTable::~HashTable()
{
	// std::cout << "Destroying the HashTable... ";
	delete[] data;
	// std::cout << "done" << std::endl;
}


HashTable::HashTable(const HashTable& b)
{
	data_end = b.data_end;

	try
	{
		data = new Item*[data_end];
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}

	for (int i = 0; i < data_end; i++)
	{
		if (b.data[i] != NULL)
		{
			data[i] = new Item(*(b.data[i]));
			data[i]->push_node(*(b.data[i]));
		}
		else
		{
			data[i] = NULL;
		}
	}
}


Value& HashTable::at(const String& key)
{
	Item *curr_item = data[get_index(key)];

	while (curr_item != NULL && curr_item->get_key() != key)
	{
		curr_item = curr_item->get_next();
	}

	if (curr_item == NULL)
	{
		throw std::invalid_argument(ERR_KEY_NOT_FOUND);
	}

	return curr_item->get_value();
}


const Value& HashTable::at(const String& key) const
{
	Item *curr_item = data[get_index(key)];

	while (curr_item != NULL && curr_item->get_key() != key)
	{
		curr_item = curr_item->get_next();
	}
	
	if (curr_item == NULL)
	{
		throw std::exception();
	}

	return curr_item->get_value();
}


size_t HashTable::size() const
{
	size_t items_num = 0;
	Item *curr_item;

	for (int i = 0; i < data_end; i++)
	{
		curr_item = data[i];

		while (curr_item != NULL)
		{
			items_num++;
			curr_item = curr_item->get_next();
		}
	}

	return items_num;
}


bool HashTable::empty() const
{
	for (int i = 0; i < data_end; i++)
	{
		if (data[i] != NULL) { return false; }
	}

	return true;
}


Value& HashTable::operator[](const String& key)
{
	Value *st = new Value(key);
	
	try
	{
		st = &(at(key));
	}
	catch (std::exception)
	{
		insert(key, *(st));
	}
	
	return *(st);
}


HashTable& HashTable::operator=(const HashTable& b)
{
	data_end = b.data_end;

	try
	{
		delete[] data;
		data = new Item*[data_end];
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


bool operator==(const HashTable& a, const HashTable& b)
{
	if (a.data_end == b.data_end)
	{
		Item *a_item, *b_item;

		for (int i = 0; i < a.data_end; i++)
		{
			a_item = a.data[i];
			b_item = b.data[i];

			while (a_item != NULL && b_item != NULL)
			{
				if (a_item->get_key() != b_item->get_key() ||
					a_item->get_value() != b_item->get_value())
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


bool operator!=(const HashTable& a, const HashTable& b)
{
	return !(a == b);
}


void HashTable::swap(HashTable& b)
{
	unsigned int tmp_data_end = this->data_end;
	Item **tmp_data = this->data;

	this->data_end = b.data_end;
	this->data = b.data;

	b.data_end = tmp_data_end;
	b.data = tmp_data;	
}


void HashTable::clear()
{
	for (int i = 0; i < data_end; i++)
	{
		data[i] = NULL;
	}
}


bool HashTable::erase(const String& key)
{
	int i= get_index(key);
	Item *last_item = data[i], *curr_item = last_item;

	if (last_item == NULL)
	{
		return false;
	}

	if (last_item->get_key() == key)
	{
		data[i] = last_item->get_next();
		return true;
	}

	while (curr_item != NULL)
	{
		if (curr_item->get_key() == key)
		{
			last_item->set_next(curr_item->get_next());
			// delete curr_item;

			return true;
		}

		last_item = curr_item;
		curr_item = curr_item->get_next();
	}

	return false;
}


bool HashTable::insert(const String& key, const Value& value)
{
	int i = get_index(key);
	Item *curr_item = data[i];

	if (curr_item == NULL)
	{
		data[i] = new Item(key, value);
		return true;
	}

	while (curr_item->get_next() != NULL)
	{
		if (curr_item->get_key() == key)
		{
			return false;
		}

		curr_item = curr_item->get_next();
	}

	if (curr_item->get_key() == key)
	{
		return false;
	}

	curr_item->set_next(new Item(key, value));

	return true;
}


bool HashTable::contains(const String& key) const
{
	try
	{
		at(key);
	}
	catch (std::exception)
	{
		return false;
	}

	return true;
}


int HashTable::get_index(const String& key) const
{
	return hash(key) % data_end;
}

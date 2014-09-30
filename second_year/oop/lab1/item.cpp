#include "htable.h"


/* -------------- ITEM METHODS -------------- */

/*
	Creates an Item object with specified key and Value object.
*/
Item::Item(const String& key, const Value& value)
{
	_key = key;

	try
	{
		_value = new Value(value);
	}
	catch (std::bad_alloc)
	{
		std::cout << ERR_BAD_ALLOC << std::endl;
	}

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
	Returns: the pointer to the next Value object in list of Value objects.
*/
Item *Item::get_next() const
{
	return _next;
}


/*
	Returns: the key of current Item object.
*/
String Item::return_key()
{
	return _key;
}


/*
	Returns: the constant key of current Item object.
*/
const String Item::return_key() const
{
	return _key;
}


/*
	Returns: the Value object from Item object.
	If Item object is empty, raises an invalid argument exception.
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
	Returns: the constant Value object from Item object.
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
	Pushes back an Item object to the list of current Item objects.
	Fails if any Item object from given Item objects list are equal
	to the key of the current Item object (when trying to create a cycled list).
*/
bool Item::push_back(Item *item)
{
	Item *p_item = item;

	if (p_item == NULL)
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

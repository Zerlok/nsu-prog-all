#include "table.h"


/* -------------- ACCESSORY FUNCTIONS -------------- */

unsigned int hash(const String key)
{
	return key.size() * key[0];
}


/* -------------- STUDENT METHODS -------------- */

Student::Student(const String _name)
{
	this->name = _name;
	this->age = 18;
	this->course = 1;
	this->average_mark = 4.0;
	this->department = "Information Technology";
}


Student::Student(const String _name, const unsigned int _age,
	const unsigned int _course, const float _average_mark,
	const String _department)
{
	this->name = _name;
	this->age = _age;
	this->course = _course;
	this->average_mark = _average_mark;
	this->department = _department;
}


Student::~Student()
{
	// std::cout << "Deleting the Student... ";
	// std::cout << "done" << std::endl;
}


Student::Student(const Student& s)
{
	this->name = s.name;
	this->age = s.age;
	this->course = s.course;
	this->average_mark = s.average_mark;
	this->department = s.department;
}


Student& Student::operator=(const Student& s)
{
	this->name = s.name;
	this->age = s.age;
	this->course = s.course;
	this->average_mark = s.average_mark;
	this->department = s.department;
}


bool operator==(const Student& a, const Student& b)
{
	return (a.name == b.name && a.age == b.age && a.course == b.course &&
		a.average_mark == b.average_mark && a.department == b.department);
}


bool operator!=(const Student& a, const Student& b)
{
	return !(a == b);
}


/* -------------- ITEM METHODS -------------- */

Item::Item(const String _key, Student& _student):
	key(_key), value(_student)
{
	this->key = _key;
	// this->value = _student;
	this->next = NULL;
}


Item::~Item()
{
	// std::cout << "Deleting the Item... ";
	// delete value;

	delete next;

	// std::cout << "done" << std::endl;
}


// Item::Item(const String _key):
// 	value(Student(key))
// {
// 	this->key = _key;
// 	this->next = NULL;
// }
 

Item::Item(const Item& i):
	value(i.value)
{
	this->key = i.key;
	// this->value = Student(i.value);
	this->next = i.next;
}


void Item::link(Item& i)
{
	this->next = &i;
}


Item& Item::operator=(const Item& i)
{
	this->key = i.key;
	this->value = i.value;
	this->next = i.next;
}

bool operator==(const Item& a, const Item& b)
{
	return (a.key == b.key && (a.value) == (b.value));
}


/* -------------- HASHTABLE METHODS -------------- */

// HashTable::HashTable()
// {
// 	HashTable::HashTable(1000);
// }


// // Destructor
// HashTable::~HashTable()
// {
// 	// std::cout << "Gonna destroy the table... ";
// 	delete[] data;
// 	// std::cout << "done" << std::endl;
// }


// HashTable::HashTable(int _mem)
// {
// 	data_end = _mem;

// 	try
// 	{
// 		data = new Item*[data_end];
// 	}
// 	catch (std::bad_alloc)
// 	{
// 		std::cout << ERR_BAD_ALLOC << std::endl;
// 	}

// 	for (int i = 0; i < data_end; i++)
// 	{
// 		data[i] = NULL;
// 	}
// }


// HashTable::HashTable(const HashTable& b)
// {
// 	data_end = b.data_end;

// 	try
// 	{
// 		data = new Item*[data_end];
// 	}
// 	catch (std::bad_alloc)
// 	{
// 		std::cout << ERR_BAD_ALLOC << std::endl;
// 	}

// 	for (int i = 0; i < data_end; i++)
// 	{
// 		data[i] = b.data[i];
// 	}
// }


// void HashTable::swap(HashTable& b)
// {
// 	unsigned int tmp_data_end = this->data_end;
// 	Item **tmp_data = this->data;

// 	this->data_end = b.data_end;
// 	this->data = b.data;

// 	b.data_end = tmp_data_end;
// 	b.data = tmp_data;	
// }


// HashTable& HashTable::operator=(const HashTable& b)
// {
// 	data_end = b.data_end;

// 	try
// 	{
// 		data = (Item**)realloc(data, sizeof(Item) * data_end);
// 	}
// 	catch (std::bad_alloc)
// 	{
// 		std::cout << ERR_BAD_ALLOC << std::endl;
// 	}

// 	for (int i = 0; i < data_end; i++)
// 	{
// 		data[i] = b.data[i];
// 	}
// }


// Item& HashTable::operator[](const String& key)
// {
// 	unsigned int h = hash(key);
// 	unsigned int index = h % data_end;

// 	Item *last_data = data[index], *curr_data = data[index];


// 	std::cout << "---> Key: "
// 				<< key
// 				<< " ("
// 				<< h
// 				<< ", "
// 				<< data_end
// 				<< ", "
// 				<< index
// 				<< ")"
// 				<< std::endl;

// 	// std::cout << "nulls: " << (last_data == NULL) << " : " << (curr_data == NULL) << std::endl;

// 	while (curr_data != NULL)
// 	{
// 		if (curr_data->name == key)
// 		{
// 			return *curr_data;
// 		}
// 		last_data = curr_data;
// 		curr_data = last_data->next;
// 	}

// 	/* If empty cell or key not found -> create a new value */
// 	Item new_item("Ivan Ivanov");

// 	if (last_data == NULL)
// 	{
// 		data[index] = &new_item;
// 	}
// 	else
// 	{
// 		last_datanew_item;
// 	}

// 	return *new_value;
// }

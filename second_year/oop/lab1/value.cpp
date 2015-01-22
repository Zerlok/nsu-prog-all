#include "htable.h"


/*
 *	-------------- VALUE CLASS METHODS --------------
 */

Value::Value(
		const String& name,
		const unsigned int age,
		const unsigned int course,
		const String& department)
{
	_name = name;
	_age = age;
	_course = course;
	_department = department;
}


Value::~Value() {}


/*
 *	Makes a copy of given Value object.
 */
Value::Value(const Value& value)
{
	_name = value._name;
	_age = value._age;
	_course = value._course;
	_department = value._department;
}


/*
 *	Copies all fields from given Value object to the current Value object.
 */
Value& Value::operator=(const Value& value)
{
	_name = value._name;
	_age = value._age;
	_course = value._course;
	_department = value._department;

	return (*this);
}


/*
 *	Checks are two Value objects same.
 *	Returns: is all fields are same in both Value objects.
 */
bool operator==(const Value& value1, const Value& value2)
{
	return ((value1._name == value2._name)
			&& (value1._age == value2._age)
			&& (value1._course == value2._course)
			&& (value1._department == value2._department)
	);
}


/*
 *	Checks are Value objects different.
 *	Returns: is NOT equal objects.
 */
bool operator!=(const Value& value1, const Value& value2)
{
	return !(value1 == value2);
}


/*
 *	Returns the value from _name field of current Value object.
 */
const String& Value::return_name() const
{
	return _name;
}
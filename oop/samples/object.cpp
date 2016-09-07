#include <iostream>
#include <string.h>
#include "object.h"


int Object::amount = 0;
int Object::idCount = 0;


void Object::init(const std::string &objName)
{
	name = objName;
	id = idCount;
	++idCount;
	++amount;
}


Object::Object()
{
	init("Object");
}


Object::Object(const std::string &objName)
{
	init(objName);
}


std::ostream &operator<<(std::ostream &output, const Object &obj)
{
	output << "[Object " << obj.id << "]: '" << obj.name << "'";
	return output;
}


Object::~Object()
{
	--amount;
}


const std::string& Object::getName() const
{
	return name;
}
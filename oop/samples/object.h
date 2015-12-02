#ifndef __OBJECT_H__
#define __OBJECT_H__


#include <iostream>
#include <string>


class Object
{
	public:
		Object();
		Object(const std::string &name);
		~Object();

		friend std::ostream &operator<<(std::ostream &output, const Object &obj);

		const std::string& getName() const;

	private:
		static int amount;
		static int idCount;
		
		int id;
		std::string name;

		void init(const std::string &objName);
};


// __OBJECT_H__
#endif

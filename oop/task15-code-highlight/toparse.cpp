stringutils::search_replace_all(line, "<", "&lt;");

#include <iostream>
#include <fstream>
#include "decorators.h"

using __my_int__ = int;


class Decorator
{
	public:
		Decorator()
			: _inner(nullptr) {}
		Decorator(Decorator* inner)
			: _inner(inner) {}
		virtual ~Decorator();

		virtual void execute(std::istream& in, std::ostream& out);

	protected:
		Decorator* _inner;
};

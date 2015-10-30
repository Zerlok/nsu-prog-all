#ifndef __FILEPARSER_H__
#define __FILEPARSER_H__


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

#include "abstractparser.h"


template <class Data>
class FileParser : public AbstractParser
{
	public:
		// Constructors / Destructor.
		FileParser(ifstream &in)
			: AbstractParser<Data>(),
			  _instream(in) {}
		~FileParser() {}

		// Overriden methods.
		bool parse_input() override
		{
			if (!((this->AbstractParser).parse_input()))
				return false;

			return true;
		}

		bool validate_input() override
		{
			if (!((this->AbstractParser).validate_input()))
				return false;

			_is_input_valid = true;
			return true;
		}

	private:
		ifstream &_instream;
};


// __FILEPARSER_H__
#endif

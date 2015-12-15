#include <ios>
#include <iomanip>
#include <sstream>
#include "datapackage.h"


const std::string DataPackage::header = "AABB";
const int DataPackage::crc_len = 4;
const int DataPackage::data_len_len = 4;
const int DataPackage::max_data_len = 128;
const int DataPackage::max_package_len = (int(DataPackage::header.size())
										  + DataPackage::crc_len
										  + DataPackage::data_len_len
										  + DataPackage::max_data_len);


DataPackage::crc_t DataPackage::count_crc(const std::string &data)
{
	crc_t _crc = 0;

	for (char c : data)
		_crc = _crc ^ c;

	std::stringstream ss;
	ss << data.size();

	for (char c : ss.str())
		_crc = _crc ^ c;

	return _crc;
}


DataPackage::DataPackage()
	: _data(""),
	  _crc(0)
{
}


DataPackage::DataPackage(int data)
{
	std::stringstream ss;
	ss << data;

	_data = ss.str();
	_crc = count_crc(_data);
}


DataPackage::DataPackage(const std::string &data)
	: _data(data),
	  _crc(count_crc(_data))
{
}


DataPackage::DataPackage(const DataPackage &package)
	: _data(package._data),
	  _crc(package._crc)
{
}


DataPackage::DataPackage(const DataPackage &&package)
	: _data(std::move(package._data)),
	  _crc(std::move(package._crc))
{
}


DataPackage::~DataPackage()
{
}


std::string &DataPackage::get_data()
{
	return _data;
}


const std::string &DataPackage::get_data() const
{
	return _data;
}


DataPackage::crc_t DataPackage::get_crc() const
{
	return _crc;
}


int DataPackage::get_data_len() const
{
	return _data.size();
}


bool DataPackage::is_valid() const
{
	return (_crc == count_crc(_data));
}


DataPackage &DataPackage::operator=(const DataPackage &package)
{
	_data = package._data;
	_crc = package._crc;

	return (*this);
}


bool DataPackage::operator==(const DataPackage &package) const
{
	return (this->_data == package._data);
}


bool DataPackage::operator!=(const DataPackage &package) const
{
	return (!((*this) == package));
}


std::istream &operator>>(std::istream &in, DataPackage &package)
{
	char chr;
	std::stringstream tmp;
	in >> std::noskipws;

	// Read header.
	for (size_t i = 0; i < DataPackage::header.size(); ++i)
	{
		in >> chr;
		tmp << chr;
	}

	if (DataPackage::header.compare(tmp.str()))
	{
		package = DataPackage();
		return in >> std::skipws;
	}

	// Read CRC.
	tmp.str("");
	for (DataPackage::crc_t i = 0; i < DataPackage::crc_len; ++i)
	{
		in >> chr;
		tmp << chr;
	}
	package._crc = std::stoi(tmp.str());

	// Read Data length.
	tmp.str("");
	for (int i = 0; i < DataPackage::data_len_len; ++i)
	{
		in >> chr;
		tmp << chr;
	}
	int data_len = std::stoi(tmp.str());

	// Read Data itself.
	tmp.str("");
	for (int i = 0; i < DataPackage::max_data_len; ++i)
	{
		if (i >= data_len)
			break;

		in >> chr;
		tmp << chr;
	}
	package._data = tmp.str();

	return in >> std::skipws;
}


std::ostream &operator<<(std::ostream &out, const DataPackage &package)
{
	out << std::setfill(DataPackage::zero_symbol)
			<< DataPackage::header
			<< std::setw(DataPackage::crc_len) << package._crc
			<< std::setw(DataPackage::data_len_len) << package.get_data_len()
			<< package._data;

	return out;
}

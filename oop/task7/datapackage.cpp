#include <ios>
#include <iomanip>
#include <sstream>
#include "datapackage.h"


const std::string DataPackage::header = "AABB";


DataPackage::crc_t DataPackage::conut_crc(const std::string &data)
{
	crc_t _crc = 0;

	for (char c : data)
		_crc = _crc ^ c;

	return _crc;
}


DataPackage::DataPackage()
	: _data(""),
	  _crc(0),
	  _len(0),
	  _is_valid(false)
{
}


DataPackage::DataPackage(const std::string &data)
	: _data(data),
	  _crc(conut_crc(_data)),
	  _len(count_package_size()),
	  _is_valid(true)
{
}


DataPackage::DataPackage(const DataPackage &package)
	: _data(package._data),
	  _crc(package._crc),
	  _len(package._len),
	  _is_valid(package._is_valid)
{
}


DataPackage::DataPackage(const DataPackage &&package)
	: _data(std::move(package._data)),
	  _crc(std::move(package._crc)),
	  _len(std::move(package._len)),
	  _is_valid(std::move(package._is_valid))
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


DataPackage::len_t DataPackage::get_size() const
{
	return _len;
}


bool DataPackage::is_valid() const
{
	return _is_valid;
}


bool DataPackage::validate()
{
	_is_valid = (_crc == conut_crc(_data));
	return _is_valid;
}


DataPackage &DataPackage::operator=(const DataPackage &package)
{
	_data = package._data;
	_crc = package._crc;
	_len = package._len;
	_is_valid = package._is_valid;

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


size_t DataPackage::count_crc_size() const
{
	std::stringstream ss;
	ss << _crc;
	return ss.str().size();
}


size_t DataPackage::count_package_size() const
{
	return _data.size();
}


std::istream &operator>>(std::istream &in, DataPackage &package)
{
	char chr;
	std::stringstream tmp;
	in >> std::noskipws;

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

	tmp.str("");
	for (DataPackage::crc_t i = 0; i < DataPackage::crc_len; ++i)
	{
		in >> chr;
		tmp << chr;
	}
	package._crc = std::stoi(tmp.str());

	tmp.str("");
	for (DataPackage::len_t i = 0; i < DataPackage::len_len; ++i)
	{
		in >> chr;
		tmp << chr;
	}
	package._len = std::stoi(tmp.str());

	tmp.str("");
	for (int i = 0; i < DataPackage::max_data_len; ++i)
	{
		if (i >= package._len)
			break;

		in >> chr;
		tmp << chr;
	}

	package._data = tmp.str();
	package._is_valid = package.validate();

	return in >> std::skipws;
}


std::ostream &operator<<(std::ostream &out, const DataPackage &package)
{
	out << std::setfill(DataPackage::none_symbol)
			<< DataPackage::header
			<< std::setw(DataPackage::crc_len) << package._crc
			<< std::setw(DataPackage::len_len) << package._len
			<< package._data;

	return out;
}

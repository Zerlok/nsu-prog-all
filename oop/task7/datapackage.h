#ifndef __DATAPACKAGE_H__
#define __DATAPACKAGE_H__


#include <iostream>
#include <string>


// Package structure: [HEADER][CRC][LEN][DATA...]
class DataPackage
{
	public:
		using crc_t = int;

		static const std::string header;
		static const int crc_len;
		static const int data_len_len;
		static const int max_data_len;
		static const int max_package_len;

		static crc_t count_crc(const std::string &data);

		DataPackage();
		DataPackage(int data);
		DataPackage(const std::string &data);
		DataPackage(const DataPackage &package);
		DataPackage(const DataPackage &&package);
		~DataPackage();

		std::string &get_data();
		const std::string &get_data() const;

		crc_t get_crc() const;
		int get_data_len() const;
		bool is_valid() const;

		DataPackage &operator=(const DataPackage &package);

		bool operator==(const DataPackage &package) const;
		bool operator!=(const DataPackage &package) const;

		friend std::istream &operator>>(std::istream &in, DataPackage &package);
		friend std::ostream &operator<<(std::ostream &out, const DataPackage &package);

	private:
		static const char zero_symbol = '0';

		std::string _data;
		crc_t _crc;
};


std::istream &operator>>(std::istream &in, DataPackage &package);
std::ostream &operator<<(std::ostream &out, const DataPackage &package);


// __DATAPACKAGE_H__
#endif

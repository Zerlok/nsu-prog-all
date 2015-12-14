#ifndef __DATAPACKAGE_H__
#define __DATAPACKAGE_H__


#include <iostream>
#include <string>

// Package structure: AABB[CRC][LEN][DATA...]
class DataPackage
{
	public:
		using crc_t = int;
		using len_t = int;

		static crc_t conut_crc(const std::string &data);

		DataPackage();
		DataPackage(const std::string &data);
		DataPackage(const DataPackage &package);
		DataPackage(const DataPackage &&package);
		~DataPackage();

		std::string &get_data();
		const std::string &get_data() const;

		crc_t get_crc() const;
		len_t get_size() const;
		bool is_valid() const;

		bool validate();
		DataPackage &operator=(const DataPackage &package);

		bool operator==(const DataPackage &package) const;
		bool operator!=(const DataPackage &package) const;

		friend std::istream &operator>>(std::istream &in, DataPackage &package);
		friend std::ostream &operator<<(std::ostream &out, const DataPackage &package);

	private:
		static const char none_symbol = '0';
		static const std::string header;
		static const len_t crc_len = 4;
		static const len_t len_len = 4;
		static const len_t max_data_len = 256;
		static const len_t max_len = (crc_len + len_len + max_data_len);

		std::string _data;
		crc_t _crc;
		len_t _len;

		bool _is_valid;

		size_t count_crc_size() const;
		size_t count_package_size() const;
};


std::istream &operator>>(std::istream &in, DataPackage &package);
std::ostream &operator<<(std::ostream &out, const DataPackage &package);


// __DATAPACKAGE_H__
#endif

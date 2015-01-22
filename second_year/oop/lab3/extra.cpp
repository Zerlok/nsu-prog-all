#include "main.h"


void show_matrix(const ScoreMatrix& matrix)
{
	for (ScoreMatrix::const_iterator it = matrix.begin();
		it != matrix.end();
		it++)
	{
		std::copy(
				(*it).first.begin(),
				(*it).first.end(),
				std::ostream_iterator<int>(std::cout, " ")
		);

		std::cout << " => ";

		std::copy(
				(*it).second.begin(),
				(*it).second.end(),
				std::ostream_iterator<int>(std::cout, " ")
		);

		std::cout << std::endl;
	}
}


void show_str_vector(const std::vector<std::string> v)
{
	std::cout << "[";
	std::copy(v.begin(), v.end(), std::ostream_iterator<std::string>(std::cout, " "));
	std::cout << "]";
}
#include "game.h"
#include <iostream>


void check_full_desk(Universe& space)
{
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			space.init(x, y, ALIVE);
		}
	}

	space.init(0, 0, DEAD);
	space.init(0, 9, DEAD);
	space.init(9, 0, DEAD);
	space.init(9, 9, DEAD);
	space.init(3, 9, DEAD);
	space.init(9, 3, DEAD);
	space.init(3, 0, DEAD);
	space.init(0, 3, DEAD);
	space.init(5, 5, DEAD);

	std::cout << "(0, 0) : " << space.get_neighbours_number(0, 0) << std::endl;
	std::cout << "(0, 9) : " << space.get_neighbours_number(0, 9) << std::endl;
	std::cout << "(9, 0) : " << space.get_neighbours_number(9, 0) << std::endl;
	std::cout << "(9, 9) : " << space.get_neighbours_number(9, 9) << std::endl;
	std::cout << "(3, 9) : " << space.get_neighbours_number(3, 9) << std::endl;
	std::cout << "(9, 3) : " << space.get_neighbours_number(9, 3) << std::endl;
	std::cout << "(3, 0) : " << space.get_neighbours_number(3, 0) << std::endl;
	std::cout << "(0, 3) : " << space.get_neighbours_number(0, 3) << std::endl;
	std::cout << "(5, 5) : " << space.get_neighbours_number(5, 5) << std::endl;
}


int main(int argc, char **argv)
{
	// if (argc == 2)
	// {
	// 	Universe space(atoi(argv[1]))
	// 	space.draw();
	// }

	Universe space(10);

	int i=9, j=8;

	space.init(9, 9, ALIVE);
	space.init(0, 9, ALIVE);
	space.init(i, j, ALIVE);

	space.draw();

	std::cout << "(0, 0) : " << space.get_neighbours_number(0, 0) << std::endl;
	std::cout << "(0, 9) : " << space.get_neighbours_number(0, 9) << std::endl;
	std::cout << "(9, 0) : " << space.get_neighbours_number(9, 0) << std::endl;
	std::cout << "(9, 9) : " << space.get_neighbours_number(9, 9) << std::endl;
	std::cout << "(3, 9) : " << space.get_neighbours_number(3, 9) << std::endl;
	std::cout << "(9, 3) : " << space.get_neighbours_number(9, 3) << std::endl;
	std::cout << "(3, 0) : " << space.get_neighbours_number(3, 0) << std::endl;
	std::cout << "(0, 3) : " << space.get_neighbours_number(0, 3) << std::endl;
	std::cout << "(5, 5) : " << space.get_neighbours_number(5, 5) << std::endl;
	std::cout << "(" << i << ", " << j << ") : " << space.get_neighbours_number(i, j) << std::endl;
	
	return 0;
}

#include "game.h"
#include <iostream>


void check_full_desk()
{
	Universe space(10);

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

	space.draw();

	// std::cout << "(0, 0) : " << space.count_neighbours(0, 0) << std::endl;
	// std::cout << "(0, 9) : " << space.count_neighbours(0, 9) << std::endl;
	// std::cout << "(9, 0) : " << space.count_neighbours(9, 0) << std::endl;
	// std::cout << "(9, 9) : " << space.count_neighbours(9, 9) << std::endl;
	// std::cout << "(3, 9) : " << space.count_neighbours(3, 9) << std::endl;
	// std::cout << "(9, 3) : " << space.count_neighbours(9, 3) << std::endl;
	// std::cout << "(3, 0) : " << space.count_neighbours(3, 0) << std::endl;
	// std::cout << "(0, 3) : " << space.count_neighbours(0, 3) << std::endl;
	// std::cout << "(5, 5) : " << space.count_neighbours(5, 5) << std::endl;
}


void check_ij_desk(int i, int j)
{
	Universe space(10);

	space.init(9, 9, ALIVE);
	space.init(0, 9, ALIVE);
	space.init(i, j, ALIVE);

	space.draw();

	// std::cout << "(0, 0) : " << space.count_neighbours(0, 0) << std::endl;
	// std::cout << "(0, 9) : " << space.count_neighbours(0, 9) << std::endl;
	// std::cout << "(9, 0) : " << space.count_neighbours(9, 0) << std::endl;
	// std::cout << "(9, 9) : " << space.count_neighbours(9, 9) << std::endl;
	// std::cout << "(3, 9) : " << space.count_neighbours(3, 9) << std::endl;
	// std::cout << "(9, 3) : " << space.count_neighbours(9, 3) << std::endl;
	// std::cout << "(3, 0) : " << space.count_neighbours(3, 0) << std::endl;
	// std::cout << "(0, 3) : " << space.count_neighbours(0, 3) << std::endl;
	// std::cout << "(5, 5) : " << space.count_neighbours(5, 5) << std::endl;
	// std::cout << "(" << i << ", " << j << ") : " << space.count_neighbours(i, j) << std::endl;
}


int main(int argc, char **argv)
{
	// if (argc == 2)
	// {
	// 	Universe space(atoi(argv[1]))
	// 	space.draw();
	// }

	// Universe space(10);

	// space.draw();

	// check_full_desk();
	
	Universe space(10);

	for (int x = 2; x < 7; x++)
	{
		for (int y = 2; y < 7; y++)
		{
			if ((x % 2 == 1) || (y % 2 == 0)) space.init(x, y, ALIVE);
		}
	}


	space.draw();

	for (int i = 0; i < 10; i++)
	{
		space.do_step();
		space.draw();
	}

	return 0;
}

#include "game.h"
#include "figures.h"
#include <iostream>


int main(int argc, char **argv)
{
	// if (argc == 1)
	// {
	// 	Universe space(STD_SIZE);
	// 	space.draw();
	// }
	
	Universe space(36);

	create_glider(1, 1, space);
	create_blinker(4, 20, space);
	create_toad(10, 20, space);
	create_block(30, 30, space);

	space.draw();

	char input_key = 'g';

	while (input_key != 'e')
	{
		space.do_step();
		space.draw();

		std::cin >> input_key;
	}

	return 0;
}

#include "game.h"
#include "figures.h"
#include <iostream>
#include <unistd.h>


enum Signal
{
	WAIT_CMD,
	EXIT_GAME,
	SAVE_GAME,
	TICK_GAME,
	SHOW_HELP
};


Signal parse_line(const std::string cmd)
{
	size_t found_dump = cmd.find("dump");
	size_t found_tick = cmd.find("tick");
	size_t found_exit = cmd.find("exit");
	size_t found_help = cmd.find("help");

	std::string answer;
	
	if (found_dump != std::string::npos)
	{
		std::cout <<  "Dumping in development." << std::endl;
	}
	else if (found_tick != std::string::npos)
	{
		std::cout << "Ticking in development." << std::endl;
	}
	else if (found_exit != std::string::npos)
	{
		std::cout << "Warning: Your game is not finished, do you really want exit? (yes/no): ";
		std::cin >> answer;

		while (answer != "yes" && answer != "no")
		{
			std::cout << "Type 'yes' or 'no': ";
			std::cin >> answer;
		}

		if (answer == "yes") return EXIT_GAME;

		return WAIT_CMD;
	}
	else if (found_help != std::string::npos)
	{
		return SHOW_HELP;
	}
	else
	{
		std::cout << "Cannot parse the command '" << cmd << "'." << std::endl;
		std::cout << "Type help to see how to use allowed commands." << std::endl;
	}

	return WAIT_CMD;
}


int main(int argc, char **argv)
{
	/* Online gameing */
	if (argc == 1)
	{
		Signal sgnl = WAIT_CMD;
		std::string line;

		std::cout << "Life Game started." << std::endl;
		std::cout << "Write your comand below, or type 'help' to see the commands you allow to use." << std::endl;

		while (sgnl == WAIT_CMD)
		{
			std::getline(std::cin, line);
			if (line != "") sgnl = parse_line(line);
		}

		switch (sgnl)
		{
			case EXIT_GAME:
			case SHOW_HELP:
			{
				exit(0);
			}
		}
	}
	
	Universe space(36);

	create_glider(1, 1, space);
	create_blinker(4, 20, space);
	create_toad(10, 20, space);
	create_block(30, 30, space);

	space.draw();

	char input_key = 'g';

	while (input_key == 'g')
	{
		space.do_step();
		space.draw();

		sleep(1);

		std::cin >> input_key;
	}

	return 0;
}

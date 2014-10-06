#include "game.h"
#include "figures.h"


enum Signal
{
	WAIT_CMD,
	SAVE_GAME,
	OPEN_GAME,
	TICK_GAME,
	DEMO_GAME,
	SHOW_HELP,
	EXIT_GAME
};


Signal parse_line(const std::string cmd, const bool is_saved_session)
{
	size_t found_dump = cmd.find("dump");
	size_t found_demo = cmd.find("demo");
	size_t found_tick = cmd.find("tick");
	size_t found_open = cmd.find("open");
	size_t found_exit = cmd.find("exit");
	size_t found_help = cmd.find("help");

	std::string answer;
	
	if (found_dump != std::string::npos)
	{
		return SAVE_GAME;
	}
	else if (found_demo != std::string::npos)
	{
		return DEMO_GAME;
	}
	else if (found_tick != std::string::npos)
	{
		return TICK_GAME;
	}
	else if (found_open != std::string::npos)
	{
		return OPEN_GAME;
	}
	else if (found_exit != std::string::npos)
	{
		if (is_saved_session) return EXIT_GAME;

		std::cout << "Warning: Your game is not saved, do you want to save it before exit? (yes/no): ";
		std::cin >> answer;

		while (answer != "yes" && answer != "no")
		{
			std::cout << "Type 'yes' or 'no': ";
			std::cin >> answer;
		}

		if (answer == "no") return EXIT_GAME;

		return SAVE_GAME;
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


void play_demo(Universe& space, int limit)
{
	int iterations = 0;

	create_glider(1, 1, space);
	create_blinker(4, 20, space);
	create_toad(10, 20, space);
	create_blinker(25, 20, space);

	while (iterations < limit)
	{
		space.draw();
		space.do_step();

		usleep(150000);
		iterations++;
	}

	space.draw();
}


int main(int argc, char **argv)
{
	/* Online gameing */
	if (argc == 1)
	{
		Signal sgnl = WAIT_CMD;
		int iterations = 200;
		int steps = 1;
		bool is_saved = false;
		Universe *space = new Universe(36);
		std::string line, filename;

		std::cout << "Life Game started." << std::endl;
		std::cout << "Write a command below, or type 'help' to see the commands you allowed to use." << std::endl;

		while (sgnl != EXIT_GAME)
		{
			std::cin >> line;
			if (line != "")
			{
				sgnl = parse_line(line, is_saved);
			}
			else
			{
				sgnl = WAIT_CMD;
			}
		
			switch (sgnl)
			{
				case DEMO_GAME:
				{
					std::cin >> iterations;
					play_demo(*space, iterations);
					break;
				}
				case TICK_GAME:
				{
					std::cout << "How many steps do you want to tick?: ";
					std::cin >> steps;
					int i = 0;
					while (i < steps) space->do_step();
					break;
				}
				case SAVE_GAME:
				{
					std::cout << "Type the file name to save the game data: ";
					std::cin >> filename;
					space->save_to_file(filename);
					is_saved = true;
					break;
				}
				case OPEN_GAME:
				{
					std::cout << "Type the file name to open the saved game: ";
					std::cin >> filename;
					delete space;
					space = new Universe(filename);
					break;
				}
				case SHOW_HELP:
				{
					std::cout << "dump - saves game into the file." << std::endl;
					std::cout << "tick - makes universe iterations." << std::endl;
					std::cout << "open - opens the saved game." << std::endl;
					std::cout << "demo - starts the demonstration." << std::endl;
					std::cout << "exit - exit the game." << std::endl;
					std::cout << "help - prints this help." << std::endl;
					break;
				}
				case EXIT_GAME:
				{
					exit(0);
				}
			}

			std::cout << "Next command: ";
		}

		std::cout << "### Warning: went out from while! ###" << std::endl;
	}
	
	return 0;
}

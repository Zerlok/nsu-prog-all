#include "game.h"
#include "figures.h"


enum Signal
{
	SAVE_GAME,
	OPEN_GAME,
	TICK_GAME,
	SHOW_HELP,
	EXIT_GAME,
	START_GAME,
	WAIT_CMD
};


Signal parse_line(const std::string cmd, const bool is_saved)
{
	size_t found_save = cmd.find("save");
	size_t found_open = cmd.find("open");
	size_t found_tick = cmd.find("tick");
	size_t found_help = cmd.find("help");
	size_t found_exit = cmd.find("exit");

	std::string answer;
	
	if (found_save != std::string::npos)
	{
		return SAVE_GAME;
	}
	else if (found_open != std::string::npos)
	{
		if (is_saved) return OPEN_GAME;

		std::cout << "Warning: The current game is not saved, do you want to save it before opening the another? (yes/no): ";
		std::cin >> answer;

		while (answer != "yes" && answer != "no")
		{
			std::cout << "Type 'yes' or 'no': ";
			std::cin >> answer;
		}

		if (answer == "no") return OPEN_GAME;

		return SAVE_GAME;
	}
	else if (found_tick != std::string::npos)
	{
		return TICK_GAME;
	}
	else if (found_help != std::string::npos)
	{
		return SHOW_HELP;
	}
	else if (found_exit != std::string::npos)
	{
		if (is_saved) return EXIT_GAME;

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
	else if (cmd == "\n" || cmd == " ")
	{
		return WAIT_CMD;
	}
	else
	{
		std::cout << "Unknown command '" << cmd << "'." << std::endl;
		std::cout << "Type help to see how to use allowed commands." << std::endl;
		return WAIT_CMD;
	}
}


void play_animation(Universe& space, int limit)
{
	int iterations = 0;

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
		Signal sgnl = START_GAME;
		int steps = 200;
		bool is_saved;
		std::string line, filename;

		/* Demo space initialization */
		Universe *space = new Universe(36);
		create_glider(1, 1, *space);
		create_blinker(4, 20, *space);
		create_toad(10, 20, *space);
		create_blinker(25, 20, *space);


		std::cout << "Life Game was started." << std::endl;
		std::cout << "Type a command, or write 'help' to see the commands you allowed to use." << std::endl;
		std::cout << "Command: ";

		while (sgnl != EXIT_GAME)
		{
			if (sgnl == START_GAME) is_saved = true;

			std::cin >> line;
			sgnl = parse_line(line, is_saved);
			
			switch (sgnl)
			{
				case SAVE_GAME:
				{
					std::cout << "Filename: ";
					std::cin >> filename;
					space->save_to_file(filename);
					is_saved = true;
					std::cout << "The universe was successfully saved to file." << std::endl;
					break;
				}
				case OPEN_GAME:
				{
					std::cout << "Filename: ";
					std::cin >> filename;
					delete space;
					space = new Universe(filename);
					std::cout << "The universe was downloaded from file successfully." << std::endl;
					break;
				}
				case TICK_GAME:
				{
					std::cout << "Steps: ";
					std::cin >> steps;
					play_animation(*space, steps);
					is_saved = false;
					break;
				}
				case SHOW_HELP:
				{
					std::cout << "save - saves game into the file." << std::endl;
					std::cout << "open - opens the saved game." << std::endl;
					std::cout << "tick - makes universe iterations." << std::endl;
					std::cout << "exit - exit the game." << std::endl;
					std::cout << "help - prints this help." << std::endl;
					break;
				}
				case EXIT_GAME:
				{
					exit(0);
				}
			}

			std::cout << "Command: ";
		}

		std::cout << "### Warning: went out from while! ###" << std::endl;
	}
	
	return 0;
}

#include "game.h"
#include "figures.h"


enum GameSignal
{
	SAVE_GAME,
	OPEN_GAME,
	TICK_GAME,
	SHOW_HELP,
	EXIT_GAME,

	START_GAME,

	UNKNOWN_CMD,
	WAIT_CMD
};


GameSignal parse_command_line(const std::string cmd, const bool is_saved)
{
	if (cmd.size() != 4)
	{
		std::cout << "Use only allowed commands (type 'help' to look for allowed command list)." << std::endl;
	}
	
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

	return UNKNOWN_CMD;
}


void play_animation(Universe& space, int limit)
{
	int iterations = 0;

	while (iterations < limit)
	{
		space.draw();
		space.do_step();

		usleep(130000); // 150000 - the normal speed.
		iterations++;
	}

	space.draw();
}


int main(int argc, char **argv) // TODO: Open a filename at first argument.
{
	GameSignal sgnl;
	std::string line, input_filename("demo/demo1.life"), output_filename("out.life");
	int steps = 1;
	bool is_saved = true;
	Universe *space;
	
	/* Online gaming */
	if (argc == 1)
	{
		sgnl = START_GAME;
	}
	else
	/* Offline gaming */
	{
		int x, arg_len = 0;

		for (int i = 0; i < argc; i++)
		{
			std::cout << i << " : '" << argv[i] << "'" << std::endl;
		}

		for (int i = 1; i < argc; i++)
		{
			arg_len = std::strlen(argv[i]);

			if (arg_len > 2 && argv[i][0] == '-' && argv[i][1] == '-') // full argument
			{
				std::cout << "Trying parse an argument: '" << argv[i] << "'" << std::endl;
			}
			else if (arg_len == 2 && argv[i][0] == '-') // flag
			{
				if (i + 1 >= argc)
				{
					std::cout << "Not enough arguments. [" << i << "] < [" << argc << "]" << std::endl;
					return 1;
				}

				switch (argv[i][1])
				{
					case 'i':
					{
						input_filename = argv[i+1];
						i++;
						break;
					}
					case 's':
					{
						steps = atoi(argv[i+1]);
						i++;
						break;
					}
					case 'o':
					{
						output_filename = argv[i+1];
						i++;
						break;
					}
					default:
					{
						std::cout << "Unknown flag." << std::endl;
						exit(1);
					}
				}
			}
			else // something else (value).
			{
				std::cout << "Please write flags or aruments." << std::endl;
				return 1;
			}
		}
	
		/* Play the offline game. */
		space = new Universe(input_filename);
		for (int i=0; i < steps; i++)
		{
			space->do_step();
		}
		space->save_to_file(output_filename);
		
		return 0;
	}

	
	/* Demo space initialization */
	space = new Universe(36);
	create_glider(1, 1, *space);
	create_blinker(4, 20, *space);
	create_toad(10, 20, *space);
	create_blinker(25, 20, *space);
	
	std::cout << "Life Game was started." << std::endl;
	std::cout << "Type a command, or write 'help' to see the commands you allowed to use." << std::endl;

	while (sgnl != EXIT_GAME)
	{
		std::cout << "Command: ";
		std::cin >> line;
		sgnl = parse_command_line(line, is_saved);
		
		switch (sgnl)
		{
			case SAVE_GAME:
			{
				std::cout << "Filename: ";
				std::cin >> output_filename;
				space->save_to_file(output_filename);
				is_saved = true;
				std::cout << "The universe was successfully saved to file." << std::endl;
				break;
			}
			case OPEN_GAME:
			{
				std::cout << "Filename: ";
				std::cin >> input_filename;
				delete space;
				space = new Universe(input_filename);
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
			case UNKNOWN_CMD:
			{
				std::cout << "Unknown command '" << line << "'." << std::endl;
				std::cout << "Type help to see how to use allowed commands." << std::endl;
			}
			case EXIT_GAME:
			{
				return 0;
			}
		}
	}

	// std::cout << "### Warning: went out from while! ###" << std::endl;

	return 0;
}

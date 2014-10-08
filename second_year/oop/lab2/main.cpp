#include "game.h"
#include "figures.h"


enum GameSignal
{
	SAVE_GAME, // Save universe to file.
	OPEN_GAME, // Open universe from file.
	TICK_GAME, // Play universe animation.
	SHOW_HELP, // Show help message.
	EXIT_GAME, // Exit the game.

	START_GAME, // Start the game.

	UNKNOWN_CMD, // The input command is unknown.
	WAIT_CMD // Wait for the command.
};


GameSignal parse_command_line(const std::string cmd, const bool is_saved)
{
	if (cmd.size() != 4)
	{
		return UNKNOWN_CMD;
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


bool is_argument(const char *line)
{
	return (std::strlen(line) > 2 && line[0] == '-' && line[1] == '-');
}


bool is_flag(const char *line)
{
	return (std::strlen(line) == 2 && line[0] == '-');
}


int main(int argc, char **argv) // TODO: Open a filename at first argument.
{
	GameSignal sgnl;
	std::string line, input_filename("demo/demo1.life"), output_filename("out.life");
	int steps = 1;
	bool is_saved = true;
	Universe *space;
	
	if (argc == 1)
	{
		sgnl = START_GAME;
	}
	else
	{
		#ifdef __DEBUG__
		for (int i = 0; i < argc; i++)
		{
			std::cout << i << " : '" << argv[i] << "'" << std::endl;
		}
		#endif

		int flag_start = 1;

		if (!is_flag(argv[1]) && !is_argument(argv[1]))
		{
			input_filename = argv[1]; // TODO: If exists!
			flag_start++;
		}
		
		/* Offline gaming */
		if (argc > 2)
		{
			for (int i = flag_start; i < argc; i++)
			{
				if (is_argument(argv[i])) // full argument
				{
					std::cout << "Trying parse an argument: '" << argv[i] << "'" << std::endl;
					std::cout << "Parsing in development." << std::endl;
				}
				else if (is_flag(argv[i])) // flag
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
						case 'h':
						{
							std::cout << "Help in dev" << std::endl;
							return 0;
						}
						default:
						{
							std::cout << "Unknown flag '" << argv[i] << "'." << std::endl;
							std::cout << "Try '-h' or '--help' for help." << std::endl;
							return 1;
						}
					}
				}
				else // something else (value).
				{
					std::cout << "Please write flags or aruments." << std::endl;
					return 1;
				}
			}
		
			/* Play offline game. */
			space = new Universe(input_filename);
			for (int i=0; i < steps; i++)
			{
				space->do_step();
			}
			space->save_to_file(output_filename);
			
			return 0;
		}
	}

	space = new Universe(input_filename);
	
	/* Online gaming */
	std::cout << "Life Game (version: 1.00 beta) was started." << std::endl;
	std::cout << "Type a command, or use 'help' to see the allowed commands." << std::endl;

	while (sgnl != EXIT_GAME)
	{
		std::cout << "Your command: ";
		std::cin >> line;
		sgnl = parse_command_line(line, is_saved);
		
		switch (sgnl)
		{
			case SAVE_GAME:
			{
				std::cin >> output_filename;
				space->save_to_file(output_filename);
				is_saved = true;
				std::cout << "The universe was successfully saved to '" << output_filename << "' file." << std::endl;
				break;
			}
			case OPEN_GAME:
			{
				std::cin >> input_filename;
				delete space;
				space = new Universe(input_filename);
				std::cout << "The universe was downloaded from '" << input_filename << "' file successfully." << std::endl;
				break;
			}
			case TICK_GAME:
			{
				std::cin >> steps;
				play_animation(*space, steps);
				is_saved = false;
				break;
			}
			case SHOW_HELP:
			{
				std::cout << "There are life game commands:" << std::endl;
				std::cout << "\tsave <filename> - saves game into the file (<filename> - string)." << std::endl;
				std::cout << "\topen <filename> - opens the saved game from file (<filename> - string)." << std::endl;
				std::cout << "\ttick <n> - makes animated <n> iterations of universe (<n> - integer)." << std::endl;
				std::cout << "\texit - exit the game." << std::endl;
				std::cout << "\thelp - prints this help message." << std::endl;
				break;
			}
			case UNKNOWN_CMD:
			{
				std::cout << "Unknown command '" << line << "'." << std::endl;
				std::cout << "Type help to see how to use allowed commands." << std::endl;
				break;
			}
			case EXIT_GAME:
			{
				return 0;
			}
		}
	}

	return 0;
}

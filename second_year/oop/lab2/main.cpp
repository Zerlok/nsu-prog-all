#include "game.h"
#include "figures.h"


enum Signal
{
	WAIT_CMD,
	EXIT_GAME,
	SAVE_GAME,
	TICK_GAME,
	DEMO_GAME,
	SHOW_HELP
};


Signal parse_line(const std::string cmd, const bool is_saved_session)
{
	size_t found_dump = cmd.find("dump");
	size_t found_demo = cmd.find("demo");
	size_t found_tick = cmd.find("tick");
	size_t found_exit = cmd.find("exit");
	size_t found_help = cmd.find("help");

	std::string answer;
	
	if (found_dump != std::string::npos)
	{
		std::cout << "Dumping in development." << std::endl;

		return SAVE_GAME;
	}
	else if (found_demo != std::string::npos)
	{
		std::cout << "Starting the demo..." << std::endl;

		return DEMO_GAME;
	}
	else if (found_tick != std::string::npos)
	{
		std::cout << "Ticking in development." << std::endl;
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
	// Universe space(36);

	create_glider(1, 1, space);
	create_blinker(4, 20, space);
	create_toad(10, 20, space);
	create_blinker(25, 20, space);
	create_blinker(30, 33, space);

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
		bool is_saved = false;
		Universe space(36);
		std::string line, filename;

		std::cout << "Life Game started." << std::endl;
		std::cout << "Write your comand below, or type 'help' to see the commands you allow to use." << std::endl;

		while (sgnl != EXIT_GAME)
		{
			std::cin >> line;
			if (line != "") sgnl = parse_line(line, is_saved);
		
			switch (sgnl)
			{
				case DEMO_GAME:
				{
					std::cin >> iterations;
					play_demo(space, iterations);
					break;
				}
				case SAVE_GAME:
				{
					std::cout << "Type the file name to save the game data: ";
					std::cin >> filename;
					space.save_to_file(filename);
					is_saved = true;
					break;
				}
				case SHOW_HELP:
				{
					std::cout << "The help in development." << std::endl;
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

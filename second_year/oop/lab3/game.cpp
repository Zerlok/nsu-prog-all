#include "main.h"


/*
 * --------------- ACCESSORY FUINCTIONS ---------------
 *
 * This functions are maden for parsing an input string
 * from console.
 *
 */

bool is_flag(const std::string line)
{
	return (line.size() == 2 && line[0] == '-');
}


bool is_argument(const std::string line)
{
	return (line.size() > 2 && line[0] == '-' && line[1] == '-');
}


bool is_value(const std::string line)
{
	return (!is_flag(line) && !is_argument(line));
}


/*
 * --------------- GAME METHODS ---------------
 */

Game::Game(int argc, char **argv)
{
	_argc = argc;
	_argv = new char*[_argc];

	for (int i = 0; i < _argc; i++)
	{
		_argv[i] = new char[std::strlen(argv[i])];
		strcpy(_argv[i], argv[i]);
	}

	#ifdef __DEBUG__
	std::cout << "The game beginning..." << std::endl;
	for (int i = 0; i < _argc; i++) std::cout << i << " : '" << _argv[i] << "'" << std::endl;
	#endif
}


Game::~Game()
{
	#ifdef __DEBUG__
	std::cout << "Exiting from the game...\nDeleting argv..." << std::endl;
	#endif
	for (int i = 0; i < _argc; i++) delete _argv[i];
	delete[] _argv;
	
	#ifdef __DEBUG__
	std::cout << "Done." << std::endl;
	#endif
}


void Game::_parse_input()
{
	int i = _argf;
	
	while (i < _argc)
	{
		if (is_argument(_argv[i]))
		{
			#ifdef __DEBUG__
			std::cout << "Trying parse an argument: '" << _argv[i] << "'" << std::endl;
			#endif
			std::cout << "Parsing in development." << std::endl;
		}
		else if (is_flag(_argv[i]))
		{
			if ((i + 1 >= _argc && _argv[i][1] != 'h')
				|| ((i + 1 < _argc) && !is_value(_argv[i + 1])))
			{
				std::cout << ERR_NOT_ENOUGH_VALUES << std::endl;
				break;
			}

			switch (_argv[i][1])
			{
				case 'h':
				{
					std::cout
							<< HELP_DESCRIPTION
							<< HELP_USAGE
							<< HELP_FLAGS
							<< std::endl;
					break;
				}
				default:
				{
					std::cout << ERR_UNKNOWN_FLAG << std::endl;
					break;
				}
			}
		}
		else // something else (value).
		{
			std::cout << ERR_NO_FLAGS << std::endl;
			break;
		}

		i++;
	}
}


bool Game::_parse_cmd()
{
	std::string cmd(_cmd);
	size_t cmd_len = cmd.size();
	std::string answer;

	if (cmd_len == 0)
	{
		return true;
	}

	size_t delimiter_pos = cmd.find(" ");
	size_t found_tick = cmd.find("tick");
	size_t found_exit = cmd.find("quit");
	size_t found_help = cmd.find("help");
	
	if (found_tick != std::string::npos)
	{
		if (delimiter_pos != std::string::npos)
		{
			// _steps_limit = atoi((_cmd.substr(delimiter_pos + 1, cmd_len - 1)).c_str());
			tick();
		}
		else
		{
			std::cout << ERR_NO_VALUE << std::endl;
		}
	}
	else if (found_help != std::string::npos && cmd_len == 4)
	{
		help();
	}
	else if (found_exit != std::string::npos && cmd_len == 4)
	{
		return false;
	}
	else
	{
		std::cout << ERR_UNKNOWN_COMMAND << std::endl;
	}

	return true;
}


bool Game::tick(int limit)
{
	std::cout << limit << std::endl;

	return true;
}


void Game::help()
{
	std::cout << HELP_COMMANDS << std::endl;
}


void Game::run()
{
	if (_is_in_background) // Run in background.
	{
		#ifdef __DEBUG__GAME__
		std::cout << "Offline gaming started:" << std::endl;
		#endif
	}
	else // Run in foreground.
	{
		bool is_running = true;

		std::cout << MSG_GREETING << std::endl;

		while (is_running)
		{
			std::cout << CMD_IN;
			getline(std::cin, _cmd);

			is_running = _parse_cmd();
		}
	}
}
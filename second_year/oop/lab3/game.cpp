#include "main.h"


/*
 * --------------- ACCESSORY FUINCTIONS ---------------
 *
 * This functions are maden for parsing an input string
 * from console.
 *
 */

/*
 * Returns is the input line a flag.
 *
 * Input:
 *    line - std::string
 *
 * Output:
 *    true / false.
 *
 * Algorithm:
 *    If it starts with '-' and it's length equals 2,
 *    then it is a flag. Otherwise - not a flag.
 */
bool is_flag(const std::string line)
{
	return (line.size() == 2 && line[0] == '-');
}


/*
 * Returns is the input line an argument.
 * If it is, then returns the '=' position in line.
 * Otherwise returns 0.
 *
 * Input:
 *    line - std::string
 *
 * Output:
 *    '=' position (true) / 0 (false).
 *
 * Algorithm:
 *    An argument must:
 *       * starts with '--' symbols
 *       * includes a '=' symbol.
 *       * includes some symbols before '=' symbol
 *       * includes some symbols after '=' symbol
 *
 * Examples (line - result):
 *    --mode=detailed - 6
 *    --n=3           - 3
 *    -t              - 0
 *    --char          - 0
 *    --=             - 0
 */
size_t is_argument(const std::string line)
{
	size_t delimiter_pos = line.find("=");
	size_t size = line.size();

	if (
		!(size > 2 && line[0] == '-' && line[1] == '-') // not starts with '--'
		|| (delimiter_pos == std::string::npos) 		// not includes '='
		|| (delimiter_pos + 1== size)					// has not got any symbol after '='
		|| (line[delimiter_pos - 1] == '-')				// has not got any symbol before '='
	) return 0;

	return delimiter_pos;
}


/*
 * Returns is the input string a value.
 *
 * Input:
 *    line - std::string
 *
 * Output:
 *    true / false.
 *
 * Algorithm:
 *    If line is not a flag and is not an argument
 *    then it is a value, otherwise - not.
 * 
 */
bool is_value(const std::string line)
{
	return (!is_flag(line) && !is_argument(line));
}


/*
 * --------------- GAME METHODS ---------------
 */

Game::Game(int argc, char **argv)
{
	/*
	 * Copy 
	 */
	_argc = argc - 1;
	_argv = new std::string[_argc];

	_mode = NULL;

	for (int i = 1; i < argc; i++)
	{
		_argv[i - 1] = std::string(argv[i]);
	}

	#ifdef __DEBUG__GAME__
	size_t eq_pos;
	bool is_flag_value = false;
	std::cout << "The input was:" << std::endl;
	for (int i = 0; i < _argc; i++) 
	{
		std::cout << i << " : " << _argv[i] << " - ";
		if (is_flag(_argv[i]))
		{
			std::cout << "('" << _argv[i][1] << "')";
			is_flag_value = (_argv[i][1] != 'h');
		}
		else if (eq_pos = is_argument(_argv[i]))
		{
			std::cout << "('"
					<< _argv[i].substr(2, eq_pos - 2)
					<< "', '"
					<< _argv[i].substr(eq_pos + 1, _argv[i].size())
					<< "')";
		}
		else if (is_flag_value)
		{
			std::cout << "value (for " << _argv[i - 1][1] << " flag)";
			is_flag_value = false;
		}

		std::cout << std::endl;
	}
	#endif

	if (_argc)
	{
		_is_in_background = true;
		_is_input_valid = _parse_input();
	}
	else
	{
		_is_in_background = false;
	}

	if (_mode == NULL)
	{
		_mode = new STD_MODE();
	}
}


Game::~Game()
{
	#ifdef __DEBUG__GAME__
	std::cout << "Exiting from the game...\nDeleting argv..." << std::endl;
	#endif
	delete[] _argv;
	
	#ifdef __DEBUG__GAME__
	std::cout << "Done." << std::endl;
	#endif
}


bool Game::_parse_input()
{
	int i = 0;
	size_t eq_pos;
	std::string arg_name, arg_value;
	
	while (i < _argc)
	{
		if (eq_pos = is_argument(_argv[i]))
		{
			arg_name = _argv[i].substr(2, eq_pos);
			arg_value = _argv[i].substr(eq_pos + 1, _argv[i].size());
			
			if (arg_name == "mode")
			{
				if (arg_value == "detailed")
				{

				}
				else if (arg_value == "fast")
				{

				}
				else if (arg_value == "tournament")
				{

				}
				else
				{
					std::cout << ERR_INVALID_MODE << std::endl;
					return false;
				}
			}
			else if (arg_name == "mode")
			{

			}
			else if (arg_name == "steps")
			{

			}
			else if (arg_name == "configs")
			{

			}
			else if (arg_name == "matrix")
			{

			}
			else
			{
				std::cout << ERR_UNKNOWN_ARGUMENT << arg_name << std::endl;
				return false;
			}
		}
		else if (is_flag(_argv[i]))
		{
			if ((i + 1 < _argc)
					&& !is_value(_argv[i + 1])
					&& _argv[i][1] != 'h'
				)
			{
				std::cout << ERR_INVALID_INPUT << std::endl;
				return false;
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
					return false;
				}
				default:
				{
					std::cout << _argv[i][1] << ERR_UNKNOWN_FLAG << std::endl;
					return false;
				}
			}
		}
		else // Not right argument or flag.
		{
			std::cout << ERR_INVALID_INPUT << std::endl;
			return false;
		}

		i++;
	}

	return true;
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
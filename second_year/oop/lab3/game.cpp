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
inline bool is_flag(const std::string line)
{
	return ((line.size() == 2)
			&& (line[0] == '-')
	);
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
inline bool is_argument(const std::string line)
{
	return ((line.size() > 2)
			&& (line[0] == '-')
			&& (line[1] == '-')
	);

	// size_t delimiter_pos = line.find("=");
	// size_t size = line.size();

	// if (
	// 	!(size > 2 && line[0] == '-' && line[1] == '-') // not starts with '--'
	// 	|| (delimiter_pos == std::string::npos) 		// not includes '='
	// 	|| (delimiter_pos + 1== size)					// has not got any symbol after '='
	// 	|| (line[delimiter_pos - 1] == '-')				// has not got any symbol before '='
	// ) return 0;

	// return delimiter_pos;
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
inline bool is_value(const std::string line)
{
	return (!is_flag(line)
			&& !is_argument(line)
	);
}


/*
 *
 */
inline bool is_exists(const char *path)
{
	struct stat info;
	int status = stat(path, &info);

	if (status != 0)
	{
		std::cout
				<< ERR_HEADER
				<< path
				<< ERR_PATH_NOT_ACCESSABLE
				<< std::endl;
		return false;
	}

	return true;
}


/*
 * --------------- GAME METHODS ---------------
 */

Game::Game(const int argc, const char **argv)
{
	/*
	 * Default settings
	 */
	_debug = false;
	_mode = new STD_MODE();
	_is_in_background = false;
	_steps_limit = STD_STEPS_LIMIT;
	_configs_dir = STD_CONFIGS_DIR;
	_matrix_file = STD_MATRIX_FILE;
	
	_parse_input(argc, argv);
}


Game::~Game()
{
	if (_debug)
	{
		std::cout << "Exiting from the game..." << std::endl;
		std::cout << "Deleting the mode class..." << std::endl;
	}
	delete _mode;
	
	if (_debug) std::cout << "Done." << std::endl;
}


void Game::_parse_input(const int argc, const char **argv)
{
	/*
	 * Copy the input arguments, flags and values.
	 */
	int __argc = argc - 1;
	std::string *__argv = new std::string[__argc];
	for (int i = 1; i < argc; i++) __argv[i - 1] = std::string(argv[i]);

	int i = 0;
	size_t equals_pos;
	std::string arg_name, arg_value;

	while (i < __argc)
	{
		/*
		 * If the argument was given.
		 */
		if (is_argument(__argv[i]))
		{
			equals_pos = __argv[i].find("=");

			if (equals_pos != std::string::npos)
			{
				arg_name = __argv[i].substr(2, equals_pos - 2);
				arg_value = __argv[i].substr(equals_pos + 1, __argv[i].size());
			}
			else if (__argv[i] == "--help")
			{
				arg_name = std::string("help");
			}
			else
			{
				std::cout
						<< ERR_HEADER
						<< __argv[i]
						<< ERR_VALUE_EXPECTED
						<< std::endl;
			}

			if (arg_name == "mode")
			{
				if (arg_value == "detailed")
				{
					delete _mode;
					_mode = new DetailedMode();
					_is_in_background = false;
				}
				else if (arg_value == "fast")
				{
					delete _mode;
					_mode = new FastMode();
					_is_in_background = true;
				}
				else if (arg_value == "tournament")
				{
					delete _mode;
					_mode = new TournamentMode();
					_is_in_background = true;
				}
				else
				{
					std::cout
							<< ERR_HEADER
							<< arg_value
							<< ERR_INVALID_MODE
							<< std::endl;
					_is_in_background = true;
				}
			}
			else if (arg_name == "steps")
			{
				if (isdigit(arg_value[0]))
				{
					_steps_limit = atoi(arg_value.c_str());
				}
				else
				{
					std::cout
							<< ERR_HEADER
							<< arg_value
							<< ERR_INTEGER_EXPECTED
							<< std::endl;
				}
			}
			else if (arg_name == "configs")
			{
				if (is_exists(arg_value.c_str()))
				{
					_configs_dir = arg_value.c_str();
				}
			}
			else if (arg_name == "matrix")
			{
				if (is_exists(arg_value.c_str()))
				{
					_matrix_file = arg_value;
				}
			}
			else if (arg_name == "help")
			{
				std::cout << HELP_USAGE << std::endl;
				_is_in_background = true;
			}
			else
			{
				std::cout
						<< ERR_HEADER
						<< arg_name
						<< ERR_UNKNOWN_ARGUMENT
						<< std::endl;
			}
		}
		/*
		 * If the flag was given.
		 */
		else if (is_flag(__argv[i]))
		{
			if ((i + 1 == __argc)
					|| !is_value(__argv[i + 1])
				)
			{
				switch (__argv[i][1])
				{
					case 'd':
					{
						std::cout
								<< WARNING_HEADER
								<< DEBUG_ENABLED
								<< std::endl;
						_debug = true;
						break;
					}
					case 'h':
					{
						std::cout << HELP_USAGE << std::endl;
						_is_in_background = true;
						break;
					}
					default: std::cout
							<< ERR_HEADER
							<< __argv[i][1]
							<< ERR_VALUE_EXPECTED
							<< std::endl;
				}
				i++;
				continue;
			}

			switch (__argv[i][1])
			{
				case 'm':
				{
					if (__argv[i + 1] == "detailed")
					{
						delete _mode;
						_mode = new DetailedMode();
						_is_in_background = false;
					}
					else if (__argv[i + 1] == "fast")
					{
						delete _mode;
						_mode = new FastMode();
						_is_in_background = true;
					}
					else if (__argv[i + 1] == "tournament")
					{
						delete _mode;
						_mode = new TournamentMode();
						_is_in_background = true;
					}
					else
					{
						std::cout
								<< ERR_HEADER
								<< __argv[i + 1]
								<< ERR_INVALID_MODE
								<< std::endl;
						_is_in_background = true;
					}

					i++;
					break;
				}
				case 's':
				{
					if (isdigit(__argv[i + 1][0]))
					{
						_steps_limit = atoi(__argv[i + 1].c_str());
					}
					else
					{
						std::cout
								<< ERR_HEADER
								<< __argv[i + 1]
								<< ERR_INTEGER_EXPECTED
								<< std::endl;
					}

					i++;
					break;
				}
				case 'c':
				{
					if (is_exists(__argv[i + 1].c_str()))
					{
						_configs_dir = __argv[i + 1].c_str();
					}
					
					i++;
					break;
				}
				case 'x':
				{
					if (is_exists(__argv[i + 1].c_str()))
					{
						_matrix_file = __argv[i + 1].c_str();
					}
					
					i++;
					break;
				}
				default: std::cout
						<< ERR_HEADER
						<< __argv[i][1]
						<< ERR_UNKNOWN_FLAG
						<< std::endl;
			}
		}
		else // Not right argument or flag.
		{
			std::cout
					<< ERR_HEADER
					<< __argv[i]
					<< ERR_INVALID_INPUT
					<< std::endl;
		}

		i++;
	} // while (i < __argc)
}


bool Game::_parse_cmd(const std::string cmd)
{
	size_t cmd_len = cmd.size();

	if (cmd_len == 0) return true;

	size_t delimiter_pos = cmd.find(" ");
	size_t found_tick = cmd.find("tick");
	size_t found_exit = cmd.find("quit");
	size_t found_help = cmd.find("help");
	size_t found_clear = cmd.find("clear");
	
	if (found_tick != std::string::npos)
	{
		if (delimiter_pos != std::string::npos)
		{
			if ((cmd_len - delimiter_pos) > MAX_INTEGER_LEN)
			{
				std::cout
						<< ERR_HEADER
						<< cmd
						<< ERR_TOO_BIG_INTEGER
						<< std::endl;
			}
			else if (!isdigit(cmd[delimiter_pos + 1]))
			{
				std::cout
						<< ERR_HEADER
						<< cmd
						<< ERR_INTEGER_EXPECTED
						<< std::endl;
			}
			else
			{
				tick(atoi(
						cmd.substr(
								delimiter_pos,
								cmd_len
						).c_str()));
			}
		}
		else
		{
			std::cout
					<< ERR_HEADER
					<< cmd
					<< ERR_VALUE_EXPECTED
					<< std::endl;
		}
	}
	else if (found_clear != std::string::npos && cmd_len == 5)
	{
		clear_screen();
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
		std::cout
				<< ERR_HEADER
			 	<< ERR_UNKNOWN_COMMAND
			 	<< std::endl;
	}

	return true;
}


void Game::tick(int limit)
{
	if (_debug) std::cout
			<< "Start ticking until "
			<< limit
			<< "..."
			<< std::endl;
}


void Game::clear_screen()
{
	system("clear");
}


void Game::help()
{
	std::cout << HELP_COMMANDS << std::endl;
}


void Game::run()
{
	if (_debug) std::cout
			<< "The game start running with configuration:\n"
			<< "   steps limit: "<< _steps_limit << std::endl
			<< "   configs dir: " << _configs_dir << std::endl
			<< "   matrix file: " << _matrix_file << std::endl
			<< std::endl;

	if (_is_in_background) // Run in background.
	{
		if (_debug) std::cout << "Gaming in background started..." << std::endl;
		
		for (int i = 0; i < _steps_limit; i++) _mode->play();
	}
	else // Run in foreground.
	{
		if (_debug) std::cout << "Gaming in foreground started..." << std::endl;

		for (int i = 0; i < _steps_limit; i++) _mode->play();

		bool is_running = true;
		std::string cmd;

		std::cout << MSG_GREETING << std::endl;

		while (is_running)
		{
			std::cout << CMD_IN;
			getline(std::cin, cmd);

			is_running = _parse_cmd(cmd);
		}
	}
}
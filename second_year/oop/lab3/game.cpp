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
	return (line.size() > 2 && line[0] == '-' && line[1] == '-');

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
bool is_value(const std::string line)
{
	return (!is_flag(line) && !is_argument(line));
}


/*
 *
 */
bool is_readable(const char *path)
{
	struct stat info;

	if (stat(path, &info) != 0)
	{
		std::cout
				<< ERR_HEADER
				<< path
				<< ERR_PATH_NOT_ACCESSABLE
				<< std::endl;
		return false;
	}
	
	if (!(info.st_mode & S_IFDIR))
	{
		std::cout
				<< ERR_HEADER
				<< path
				<< ERR_PATH_NOT_EXISTS
				<< std::endl;
		return false;
	}
	
	return true;
}


/*
 * --------------- GAME METHODS ---------------
 */

Game::Game(int argc, char **argv)
{
	#ifdef __DEBUG__GAME__
	std::cout
			<< WARNING_HEADER
			<< "you have started the game in debug mode!\n" << std::endl;
	#endif

	/*
	 * Default settings
	 */
	_mode = new STD_MODE();
	_steps_limit = STD_STEPS_LIMIT;
	_configs_dir = STD_CONFIGS_DIR;
	_matrix_file = STD_MATRIX_FILE;

	if (argc > 1)
	{
		_is_in_background = true;
		_parse_input(argc, argv);
	}
	else
	{
		_is_in_background = false;
	}
}


Game::~Game()
{
	#ifdef __DEBUG__GAME__
	std::cout << "Exiting from the game..." << std::endl;
	std::cout << "Deleting the mode class..." << std::endl;
	#endif
	delete _mode;
	
	#ifdef __DEBUG__GAME__
	std::cout << "Done." << std::endl;
	#endif
}


void Game::_parse_input(int argc, char **argv)
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
		if (__argv[i] == "-h" || __argv[i] == "--help")
		{
			std::cout
					<< HELP_DESCRIPTION << std::endl
					<< HELP_USAGE << std::endl
					<< HELP_FLAGS << std::endl
					<< std::endl;
			break;
		}

		if (is_argument(__argv[i]))
		{
			equals_pos = __argv[i].find("=");

			if (equals_pos != std::string::npos)
			{
				arg_name = __argv[i].substr(2, equals_pos - 2);
				arg_value = __argv[i].substr(equals_pos + 1, __argv[i].size());
			}
			else
			{
				std::cout
						<< ERR_HEADER
						<< __argv[i]
						<< ERR_VALUE_EXPECTED
						<< std::endl;
			}
			
			#ifdef __DEBUG__GAME__
			std::cout
					<< "arg: '"
					<< arg_name
					<< "' : '"
					<< arg_value
					<< "'"
					<< std::endl;
			#endif

			if (arg_name == "mode")
			{
				if (arg_value == "detailed")
				{
					delete _mode;
					_mode = new DetailedMode();
				}
				else if (arg_value == "fast")
				{
					delete _mode;
					_mode = new FastMode();
				}
				else if (arg_value == "tournament")
				{
					delete _mode;
					_mode = new TournamentMode();
				}
				else
				{
					std::cout
							<< ERR_HEADER
							<< arg_value
							<< ERR_INVALID_MODE
							<< std::endl;
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
				if (is_readable(arg_value.c_str()))
				{
					_configs_dir = arg_value.c_str();
				}
			}
			else if (arg_name == "matrix")
			{
				if (is_readable(arg_value.c_str()))
				{
					_matrix_file = arg_value;
				}
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
		else if (is_flag(__argv[i]))
		{
			#ifdef __DEBUG__GAME__
			std::cout
					<< "flag: '"
					<< __argv[i][1]
					<< "' : '"
					<< __argv[i + 1]
					<< "'"
					<< std::endl;
			#endif
			
			if ((i + 1 == __argc)
					&& !is_value(__argv[i + 1])
				)
			{
				std::cout
						<< ERR_HEADER
						<< __argv[i][1]
						<< ERR_VALUE_EXPECTED
						<< std::endl;
				i++;
			}

			switch (__argv[i][1])
			{
				default:
				{
					std::cout
							<< ERR_HEADER
							<< __argv[i][1]
							<< ERR_UNKNOWN_FLAG
							<< std::endl;
				}
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
	}
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
				tick(atoi(cmd.substr(delimiter_pos, cmd_len).c_str()));
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
		std::cout << ERR_UNKNOWN_COMMAND << std::endl;
	}

	return true;
}


bool Game::tick(int limit)
{
	std::cout << limit << std::endl;

	return true;
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
	if (_is_in_background) // Run in background.
	{
		#ifdef __DEBUG__GAME__
		std::cout
				<< "Offline gaming started, configuration:" << std::endl
				<< "   steps limit: "<< _steps_limit << std::endl
				<< "   configs dir: " << _configs_dir << std::endl
				<< "   matrix file: " << _matrix_file << std::endl
				<< std::endl;
		#endif
	}
	else // Run in foreground.
	{
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
#include "main.h"

#include "strategy.h"
#include "factory.h"
#include "mode.h"
#include "game.h"


/*
 * --------------- EXTRA FUINCTIONS ---------------
 *
 * This functions are maden for parsing the input string
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
inline bool is_flag(const std::string& line)
{
	return ((line.size() == 2)
			&& (line[0] == '-')
	);
}


/*
 * Returns is the input line an argument.
 *
 * Input:
 *    line - std::string
 *
 * Output:
 *    '=' position (true) / 0 (false).
 *
 * Algorithm:
 *    An argument must starts with '--' symbols.
 */
inline bool is_argument(const std::string& line)
{
	return ((line.size() > 2)
			&& (line[0] == '-')
			&& (line[1] == '-')
	);
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
inline bool is_value(const std::string& line)
{
	return (!is_flag(line)
			&& !is_argument(line)
	);
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
	_is_valid_input = true;
	_is_in_background = false;
	_steps_limit = STD_STEPS_LIMIT;
	_mode_str = "none";
	_matrix = NULL;
	_configs_dir = STD_CONFIGS_DIR;
	
	_parse_input(argc, argv);

	if (_is_valid_input)
	{
		if (_matrix == NULL)
			_matrix = STD_MATRIX;

		if ((_mode_str == "detailed")
			|| (_mode_str == "none"))
			_mode = new DetailedMode(&_matrix, _configs_dir);

		else if (_mode_str == "detailed")
			_mode = new FastMode(&_matrix, _configs_dir);

		else if (_mode_str == "detailed")
			_mode = new TournamentMode(&_matrix, _configs_dir);
	}
}


Game::~Game()
{
	if (_debug) std::cout
			<< DBG_HEADER
			<< "Exiting from the game..."
			<< std::endl;

	if (_debug) std::cout
			<< DBG_HEADER
			<< "Deleting the mode class..."
			<< std::endl;

	delete _mode;
	
	if (_debug) std::cout
			<< DBG_HEADER
			<< "Done."
			<< std::endl;
}


/*
 * Game input parsing method:
 *    This method matches input with available flags and arguments,
 *    which you can specify when running the game, and validates the
 *    input data.
 *
 *    If input is valid, then the game will be started, otherwise
 *    game will be finished.
 */
void Game::_parse_input(const int argc, const char **argv)
{
	int i = 0;
	size_t equals_pos;
	std::string arg_name;
	std::string arg_value;
	std::vector<std::string> c_argv;

	for (int j = 1; j < argc; j++)
	{
		c_argv.push_back(std::string(argv[j]));
		// std::cout << c_argv[i] << std::endl;
	}

	while ((i < argc - 1)
			&& _is_valid_input)
	{
		/*
		 * If an argument was given
		 */
		if (is_argument(c_argv[i]))
		{
			equals_pos = c_argv[i].find("=");

			if (equals_pos != str_none)
			{
				arg_name = c_argv[i].substr(2, equals_pos - 2);
				arg_value = c_argv[i].substr(equals_pos + 1, c_argv[i].size() - equals_pos - 1);
			}
			else
			{
				arg_name = c_argv[i].substr(2, c_argv[i].size() - 2);
				arg_value = "";
			}

			if (arg_name == "mode")
			{
				if (arg_value == "")
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< arg_name
							<< ERR_ARG_VALUE_EXPECTED
							<< std::endl;
					break;
				}

				if ((arg_value == "detailed")
					|| (arg_value == "fast")
					|| (arg_value == "tournament"))
				{
					_mode_str = arg_value;
				}
				else
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< arg_value
							<< ERR_INVALID_MODE
							<< std::endl;
					break;
				}
			}
			else if (arg_name == "steps")
			{
				if (arg_value == "")
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< arg_name
							<< ERR_ARG_VALUE_EXPECTED
							<< std::endl;
					break;
				}
				else if (!isdigit(arg_value[0]))
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< arg_name
							<< ERR_ARG_VALUE_EXPECTED
							<< std::endl;
					break;
				}
				
				_is_in_background = true;
				_steps_limit = atoi(arg_value.c_str());
			}
			else if (arg_name == "configs")
			{
				if (arg_value == "")
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< arg_name
							<< ERR_ARG_VALUE_EXPECTED
							<< std::endl;
					break;
				}

				_configs_dir = arg_value.c_str();
			}
			else if (arg_name == "matrix")
			{
				if (arg_value == "")
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< arg_name
							<< ERR_ARG_VALUE_EXPECTED
							<< std::endl;
					break;
				}

				_matrix_file = arg_value;
			}
			else if (arg_name == "debug")
			{
				_debug = true;
				std::cout
						<< DBG_HEADER
						<< DEBUG_ENABLED
						<< std::endl;
			}
			else if (arg_name == "help")
			{
				_is_in_background = true;
				std::cout << HELP_USAGE << std::endl;
			}
			else
			{
				_is_valid_input = false;
				std::cout
						<< ERR_HEADER
						<< arg_name
						<< ERR_UNKNOWN_ARGUMENT
						<< std::endl;
				break;
			} // endif
		} // endif
		/*
		 * If the flag was given.
		 */
		else if (is_flag(c_argv[i]))
		{
			switch (c_argv[i][1])
			{
				case 'm': // for mode
				{
					if ( ! ((i + 1 < argc)
						&& is_value(c_argv[i + 1])))
					{
						_is_valid_input = false;
						std::cout
								<< ERR_HEADER
								<< c_argv[i][1]
								<< ERR_FLAG_VALUE_EXPECTED
								<<std::endl;
						break;
					}

					if ((c_argv[i + 1] == "detailed")
						|| (c_argv[i + 1] == "fast")
						|| (c_argv[i + 1] == "tournament"))
					{
						_mode_str = c_argv[i + 1];
					}
					else
					{
						_is_valid_input = false;
						std::cout
								<< ERR_HEADER
								<< c_argv[i + 1]
								<< ERR_INVALID_MODE
								<< std::endl;
						break;
					}

					i++;
					break;
				} // endcase
				case 's': // for steps
				{
					if ( ! ((i + 1 < argc)
						&& is_value(c_argv[i + 1])))
					{
						_is_valid_input = false;
						std::cout
								<< ERR_HEADER
								<< c_argv[i][1]
								<< ERR_FLAG_VALUE_EXPECTED
								<<std::endl;
						break;
					}
					else if (!isdigit(c_argv[i + 1][0]))
					{
						_is_valid_input = false;
						std::cout
								<< ERR_HEADER
								<< c_argv[i + 1]
								<< ERR_INTEGER_EXPECTED
								<< std::endl;
						break;
					}

					_is_in_background = true;
					_steps_limit = atoi(c_argv[i + 1].c_str());

					i++;
				} // endcase
				case 'c': // for configs
				{
					if ( ! (
						(i + 1 < argc)
						&& is_value(c_argv[i + 1])))
					{
						_is_valid_input = false;
						std::cout
								<< ERR_HEADER
								<< c_argv[i]
								<< ERR_FLAG_VALUE_EXPECTED
								<< std::endl;
						break;
					}

					_configs_dir = c_argv[i + 1].c_str();

					i++;
					break;
				} // endcase
				case 'x': // for matrix
				{
					if ( ! (
						(i + 1 < argc)
						&& is_value(c_argv[i + 1])))
					{
						_is_valid_input = false;
						std::cout
								<< ERR_HEADER
								<< c_argv[i]
								<< ERR_FLAG_VALUE_EXPECTED
								<< std::endl;
						break;
					}
					
					_matrix_file = c_argv[i + 1].c_str();
					
					i++;
					break;
				} // endcase
				case 'h': // for help
				{
					_is_in_background = true;
					std::cout
							<< HELP_DESCRIPTION
							<< HELP_USAGE
							<< HELP_FLAGS
							<< std::endl;
					break;
				} // endcase
				default:
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< c_argv[i]
							<< ERR_UNKNOWN_FLAG
							<< std::endl;
					break;
				} // endcase
			} // endswitch
		} // endif
		else
		{
			_is_valid_input = false;
			std::cout
					<< ERR_HEADER
					<< c_argv[i]
					<< ERR_INVALID_INPUT
					<< std::endl;
		} // endif

		i++;
	} // endwhile
}


bool Game::_parse_cmd(const std::string& cmd)
{
	size_t cmd_len = cmd.size();

	if (cmd_len == 0)
		return true;

	size_t delimiter_pos = cmd.find(" ");

	size_t found_clear = cmd.find("clear");
	size_t found_exit = cmd.find("quit");
	size_t found_help = cmd.find("help");
	size_t found_step = cmd.find("step");
	size_t found_tick = cmd.find("tick");
	size_t found_use = cmd.find("use");
	size_t found_show = cmd.find("show");
	size_t found_scores = cmd.find("scores");
	size_t found_strategies = cmd.find("strategies");

	if ((found_tick == 0)
		&& ((delimiter_pos == 4)
			|| (cmd_len == 4)))
	{
		if ((cmd_len > 5)
			&& isdigit(cmd[5]))
		{
			_steps_limit = atoi(cmd.substr(delimiter_pos, cmd_len).c_str());
			tick();
		}
		else std::cout
				<< ERR_HEADER
				<< cmd
				<< ERR_INTEGER_EXPECTED
				<< std::endl;
	}
	else if ((found_clear == 0)
		&& (cmd_len == 5))
	{
		clear_screen();
	}
	else if ((found_use == 0)
		&& ((delimiter_pos == 3)
			|| (cmd_len == 3)))
	{
		if (cmd_len > 5)
		{

		}
		else std::cout
				<< ERR_HEADER
				<< cmd
				<< ERR_CMD_VALUE_EXPECTED
				<< std::endl;
	}
	else if ((found_show == 0)
		&& ((delimiter_pos == 4)
			|| (cmd_len == 4)))
	{
		if ((found_strategies == 5)
			&& cmd_len == 15))
			list_strategies();

		else if ((found_scores == 5)
			&& cmd_len == 11))
			list_scores();

		else std::cout
				<< ERR_HEADER
				<< cmd
				<< ERR_CMD_INVALID_VALUE
				<< std::endl;
	}
	else if ((found_help != str_none) && (cmd_len == 4))
	{
		help();
	}
	else if ((found_exit != str_none) && (cmd_len == 4))
	{
		return false;
	}
	else std::cout
			<< ERR_HEADER
			<< cmd
		 	<< ERR_UNKNOWN_COMMAND
		 	<< std::endl;
	
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


void Game::list_strategies()
{
	std::cout << "list strategies" << std::endl;
}


void Game::list_scores()
{
	std::cout << "list scores" << std::endl;
}


void Game::help()
{
	std::cout << HELP_COMMANDS << std::endl;
}


void Game::run()
{
	if (_debug) std::cout
			<< "The game start running with configuration:\n"
			<< "   valid input: " << _is_valid_input << "\n"
			<< "   steps limit: " << _steps_limit << "\n"
			<< "   configs dir: " << _configs_dir << "\n"
			<< "   matrix file: " << _matrix_file << "\n"
			<< std::endl;

	if (!_is_valid_input)
		return;

	_mode->setup(
			new TrustfulStrategy(),
			new MistrustfulStrategy(),
			new CrazyStrategy());

	if (_is_in_background) // Run in background.
	{
		if (_debug) std::cout
				<< "Gaming in background started..."
				<< std::endl;

		_mode->play();
		// for (int i = 0; i < _steps_limit; i++)
		// 	_mode->play();
	}
	else // Run in foreground.
	{
		if (_debug) std::cout
				<< "Gaming in foreground started..."
				<< std::endl;

		_mode->play();
		// for (int i = 0; i < _steps_limit; i++) _mode->play();

		// bool is_running = true;
		// std::string cmd;

		// std::cout << MSG_GREETING << std::endl;

		// while (is_running)
		// {
		// 	std::cout << CMD_IN;
		// 	getline(std::cin, cmd);

		// 	is_running = _parse_cmd(cmd);
		// }
	}
}
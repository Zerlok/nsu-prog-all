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


const ScoreMatrix get_default_matrix()
{
	ScoreMatrix m;

	m[{cooperate, cooperate, cooperate}] = {4, 4, 4};
	m[{cooperate, cooperate, defect   }] = {2, 2, 5};
	m[{cooperate, defect,    cooperate}] = {2, 5, 2};
	m[{cooperate, defect,    defect   }] = {0, 3, 3};
	m[{defect,    cooperate, cooperate}] = {5, 2, 2};
	m[{defect,    cooperate, defect   }] = {3, 0, 3};
	m[{defect,    defect,    cooperate}] = {3, 3, 0};
	m[{defect,    defect,    defect   }] = {1, 1, 1};

	return m;
}


const ScoreMatrix get_matrix_from_file(
		std::string& matrix_path)
{
	return get_default_matrix();
}


std::vector<std::string> get_several_randoms(
		const std::vector<std::string>& list,
		int limit)
{
	int len = list.size();
	std::vector<std::string> choices;

	if (len == 0)
		return choices;

	for (int i = 0; i < limit; i++)
		choices.push_back(list[rand() % len]);

	return choices;
}


/*
 * --------------- GAME METHODS ---------------
 */

Game::Game(
		const int argc,
		const char **argv,
		const StrategyFactory& factory)
	: _is_valid_input(true), _is_in_background(false),
	_steps_limit(STD_STEPS_LIMIT), _mode_name(STD_MODE_NAME), _mode(NULL),
	_matrix_path(STD_MATRIX_PATH), _configs_path(STD_CONFIGS_PATH)
{
	if (DEBUG) std::cout
			<< DBG_HEADER
			<< "Creating the game..."
			<< std::endl;

	// Randomize
	time_t t;
	time(&t);
	
	srand((unsigned int) t);
	
	_parse_input(argc, argv);

	if (_is_valid_input)
	{
		ScoreMatrix matrix;

		if (_init_names.empty())
			_init_names = get_several_randoms(factory.get_registered(), 3);

		if (_matrix_path.empty())
			matrix = get_default_matrix();

		else
			matrix = get_matrix_from_file(_matrix_path);

		if (_mode_name == "detailed")
		{
			if (_init_names.size() != 3)
			{
				_is_valid_input = false;
				std::cout
						<< ERR_HEADER
						<< _init_names.size()
						<< ERR_INVLID_STRATEGIES_AMMOUNT
						<< std::endl;
			}

			_mode = new DetailedMode(
					factory,
					_init_names,
					matrix,
					_configs_path);
		}
		else if (_mode_name == "fast")
		{
			if (_init_names.size() != 3)
			{
				_is_valid_input = false;
				std::cout
						<< ERR_HEADER
						<< _init_names.size()
						<< ERR_INVLID_STRATEGIES_AMMOUNT
						<< std::endl;
			}

			_mode = new FastMode(
					factory,
					_init_names,
					matrix,
					_configs_path);
		}
		else if (_mode_name == "tournament")
		{
			if (_init_names.size() < 3)
			{
				_is_valid_input = false;
				std::cout
						<< ERR_HEADER
						<< _init_names.size()
						<< ERR_STRATEGIES_IS_NOT_ENOUGH
						<< std::endl;
			}

			_mode = new TournamentMode(
					factory,
					_init_names,
					matrix,
					_configs_path);
		}
	}

	if (DEBUG) std::cout
			<< DBG_HEADER
			<< "Game creating finished."
			<< std::endl;
}


Game::~Game()
{
	if (DEBUG) std::cout
			<< DBG_HEADER
			<< "Exiting from the game..."
			<< std::endl;

	if (DEBUG) std::cout
			<< DBG_HEADER
			<< "Deleting the mode class..."
			<< std::endl;

	delete _mode;
	
	if (DEBUG) std::cout
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
	if (DEBUG) std::cout
			<< DBG_HEADER
			<< "Parsing the input..."
			<< std::endl;

	int i = 0;
	size_t equals_pos;
	std::string arg_name;
	std::string arg_value;
	std::vector<std::string> c_argv;

	// Copy-paste argv into c_argv
	for (int j = 1; j < argc; j++)
	{
		c_argv.push_back(std::string(argv[j]));

		if (DEBUG) std::cout
				<< c_argv[j - 1]
				<< std::endl;
	}

	// Read initial strategies
	while ((i < argc - 1)
		&& is_value(c_argv[i]))
		_init_names.push_back(c_argv[i++]);

	// Move along flags and arguments
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
							<< ERR_VALUE_EXPECTED
							<< std::endl;
					break;
				}

				if ((arg_value == "detailed")
					|| (arg_value == "fast")
					|| (arg_value == "tournament"))
				{
					_mode_name = arg_value;
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
							<< ERR_VALUE_EXPECTED
							<< std::endl;
					break;
				}
				else if (!isdigit(arg_value[0]))
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< arg_name
							<< ERR_VALUE_EXPECTED
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
							<< ERR_VALUE_EXPECTED
							<< std::endl;
					break;
				}

				_configs_path = arg_value.c_str();
			}
			else if (arg_name == "matrix")
			{
				if (arg_value == "")
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< arg_name
							<< ERR_VALUE_EXPECTED
							<< std::endl;
					break;
				}

				_matrix_path = arg_value;
			}
			else if (arg_name == "debug")
			{
				DEBUG = true;
				std::cout
						<< DBG_HEADER
						<< DBG_ENABLED
						<< std::endl;
			}
			else if (arg_name == "help")
			{
				_is_in_background = true;
				std::cout
						<< HELP_DESCRIPTION << "\n"
						<< HELP_USAGE << "\n"
						<< HELP_FLAGS << "\n"
						<< HELP_AVAILABLE_MODES << "\n"
						<< std::endl;
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
								<< ERR_VALUE_EXPECTED
								<<std::endl;
						break;
					}

					if ((c_argv[i + 1] == "detailed")
						|| (c_argv[i + 1] == "fast")
						|| (c_argv[i + 1] == "tournament"))
					{
						_mode_name = c_argv[i + 1];
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
								<< ERR_VALUE_EXPECTED
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
								<< ERR_VALUE_EXPECTED
								<< std::endl;
						break;
					}

					_configs_path = c_argv[i + 1];

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
								<< ERR_VALUE_EXPECTED
								<< std::endl;
						break;
					}
					
					_matrix_path = c_argv[i + 1];
					
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

	if (DEBUG) std::cout
			<< DBG_HEADER
			<< "Input parsing finished."
			<< std::endl;
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
	size_t found_tick = cmd.find("tick");
	size_t found_use = cmd.find("use");
	size_t found_list = cmd.find("list");

	if ((found_tick == 0)
		&& ((delimiter_pos == 4)
			|| (cmd_len == 4)))
	{
		if ((cmd_len > 5)
			&& isdigit(cmd[5]))
		{
			_steps_limit = atoi(cmd.substr(delimiter_pos, cmd_len).c_str());
			cmd_tick();
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
		cmd_clear();
	}
	else if ((found_use == 0)
			&& ((delimiter_pos == 3)
				|| (cmd_len == 3)))
	{
		if (cmd_len > 5)
		{
			std::vector<std::string> names;
			std::string substr = cmd.substr(delimiter_pos + 1, cmd_len - 4);
			std::istringstream iss (substr);

			std::copy(
					std::istream_iterator<std::string>(iss),
					std::istream_iterator<std::string>(),
					std::back_inserter(names));

			cmd_use(names);
		}
		else std::cout
				<< ERR_HEADER
				<< cmd
				<< ERR_VALUE_EXPECTED
				<< std::endl;
	}
	else if ((found_list == 0)
			&& (cmd_len == 4))
	{
		cmd_list();
	}
	else if ((found_help != str_none)
			&& (cmd_len == 4))
	{
		cmd_help();
	}
	else if ((found_exit != str_none)
			&& (cmd_len == 4))
	{
		return false;
	}
	else std::cout
			<< ERR_HEADER
			<< cmd
		 	<< ERR_UNKNOWN_CMD
		 	<< std::endl;
	
	return true;
}


void Game::cmd_tick()
{
	if (DEBUG) std::cout
			<< "Start ticking until " << _steps_limit << " ..."
			<< std::endl;

	_mode->play(_steps_limit);
	show_scores();
}


void Game::cmd_clear()
{
	system("clear");
}


void Game::cmd_list()
{
	std::cout << "List of available strategies:" << std::endl;

	show_str_vector(_mode->get_available_strategies_names());

	std::cout << std::endl;
}


void Game::cmd_use(
		const std::vector<std::string>& names)
{
	_mode->use(names);
}


void Game::show_scores()
{
	std::cout << "Total scores:" << std::endl;

	std::vector<std::string> names = _mode->get_current_strategies_names();
	std::vector<int> scores = _mode->get_scores();

	int width = names[0].size() + 3;

	for (int i = 0; i < names.size(); i++) std::cout
			<< std::setw(width) << names[i] << " : " << scores[i] << std::endl;
}


void Game::cmd_help()
{
	std::cout
			<< HELP_COMMANDS
			<< std::endl;
}


void Game::run()
{
	if (DEBUG)
	{
		std::cout
			<< "\n"
			<< "The game was started with configuration:\n"
			<< "   valid input: " << _is_valid_input << "\n"
			<< "   steps limit: " << _steps_limit << "\n"
			<< "   configs dir: " << _configs_path << "\n"
			<< "   matrix file: " << _matrix_path << "\n"
			<< "     mode name: " << _mode_name << "\n"
			<< "     init list: ";
			show_str_vector(_init_names);
			std::cout << "\n" << std::endl;
	}

	if (!_is_valid_input)
		return;


	if (_is_in_background) // Run in background.
	{
		if (DEBUG) std::cout
				<< "Gaming in background started..."
				<< std::endl;

		_mode->play(_steps_limit);

		if (_steps_limit > 0)
			show_scores();
	}
	else // Run in foreground.
	{
		if (DEBUG) std::cout
				<< "Gaming in foreground started..."
				<< std::endl;

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
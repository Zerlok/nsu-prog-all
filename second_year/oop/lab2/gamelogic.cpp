#include "main.h"
#include "lifeform.h"
#include "universe.h"
#include "gamelogic.h"

#include <sys/stat.h>


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
bool is_flag(const std::string& line)
{
	return (line.size() == 2 && line[0] == '-');
}


/*
 * Returns is the input line an argument.
 *
 * Input:
 *    line - std::string
 *
 * Output:
 *    true) / false.
 *
 * Algorithm:
 *    An argument must starts with '--' symbols.
 */
bool is_argument(const std::string& line)
{
	return (line.size() > 2 && line[0] == '-' && line[1] == '-');
}


/*
 * Returns is the input line a value.
 *
 * Input:
 *    line - std::string
 *
 * Output:
 *    true) / false.
 *
 * Algorithm:
 *    If line is not a flag and not an argument,
 *    then it is a value.
 */
bool is_value(const std::string& line)
{
	return (!is_flag(line) && !is_argument(line));
}


/*
 * --------------- GAME CLASS METHODS ---------------
 *
 * Next functions declares whole logic of the game.
 *
 */

/*
 * Game constructor:
 *    This method initializes game data from argc and argv variables,
 *    which your main program recieves when it runs.
 */
Game::Game(int argc, char **argv)
{
	_debug = false;

	_is_valid_input = true;
	_online = true;
	_saved = true;
	_space = NULL;
	_steps_limit = 0;
	_output_filename = std::string(STD_OUTPUT_FILENAME);

	_parse_input(argc, argv); // Read _steps_limit, _output_filename, _input_filename from argv.

	if (_is_valid_input)
		_space = new Universe(_input_filename); // Open the universe from file.

	if (_debug) std::cout
			<< DBG_HEADER
			<< "Game was started with next properties:\n"
			<< "    debug:  " << _debug << "\n"
			<< "    valid:  " << _is_valid_input << "\n"
			<< "    online: " << _online << "\n"
			<< "    input:  " << _input_filename << "\n"
			<< "    output: " << _output_filename << "\n";
}


/*
 * Game destructor:
 *    This method erases all game data (used when exiting from the game).
 */
Game::~Game()
{
	if (_debug) std::cout
			<< DBG_HEADER
			<< "Exiting from the game..."
			<< std::endl;
	
	if (_debug) std::cout
			<< DBG_HEADER
			<< "Deleting space..."
			<< std::endl;
	
	delete _space;

	if (_debug)std::cout
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
void Game::_parse_input(int argc, char **argv)
{
	int i;
	size_t equals_pos;
	std::string arg_name;
	std::string arg_value;
	std::vector<std::string> c_argv;

	for (i = 0; i < argc; i++)
	{
		c_argv.push_back(std::string(argv[i]));
		// std::cout << c_argv[i] << std::endl;
	}

	// The saved game is specified at input as a value.
	if (argc > 1 && is_value(c_argv[1]))
	{
		i = 2;
		_input_filename = std::string(argv[1]);
	}
	// The saved game is not specified.
	else
	{
		i = 1;
		_input_filename = std::string(STD_INPUT_FILENAME);
	}
	
	while ((i < argc) && (_is_valid_input))
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
			
			if (arg_name == "iterations")
			{
				if (arg_value != "")
				{
					_online = false;
					_steps_limit = atoi(arg_value.c_str());
				}
				else
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< arg_name
							<< ERR_ARG_VALUE_EXPECTED
							<< std::endl;
					
					break;
				}
			}
			else if (arg_name == "output")
			{
				if (arg_value != "")
				{
					_output_filename = arg_value;
				}
				else
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< arg_name
							<< ERR_ARG_VALUE_EXPECTED
							<< std::endl;
					
					break;
				}
			}
			else if (arg_name == "help")
			{
				_online = false;
				std::cout
						<< HELP_DESCRIPTION
						<< HELP_USAGE
						<< HELP_FLAGS
						<< std::endl;
			}
			else if (arg_name == "debug")
			{
				_debug = true;
				std::cout
						<< DBG_HEADER
						<< MSG_DEBUG_ENABLED
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
			}
		}

		/*
		 * If a flag was given
		 */
		else if (is_flag(c_argv[i]))
		{
			switch (c_argv[i][1])
			{
				case 'i':
				{
					if ((i + 1 < argc) && is_value(c_argv[i + 1]))
					{
						_online = false;
						_steps_limit = atoi(c_argv[++i].c_str());
					}
					else
					{
						_is_valid_input = false;
						std::cout
								<< ERR_HEADER
								<< c_argv[i]
								<< ERR_FLAG_VALUE_EXPECTED
								<< std::endl;
					}
					break;
				}
				case 'o':
				{
					if ((i + 1 < argc) && is_value(c_argv[i + 1]))
					{
						_output_filename = c_argv[++i];
					}
					else
					{
						_is_valid_input = false;
						std::cout
								<< ERR_HEADER
								<< c_argv[i]
								<< ERR_FLAG_VALUE_EXPECTED
								<< std::endl;
					}
					break;
				}
				case 'h':
				{
					_online = false;
					std::cout
							<< HELP_DESCRIPTION
							<< HELP_USAGE
							<< HELP_FLAGS
							<< std::endl;
					break;
				}
				default:
				{
					_is_valid_input = false;
					std::cout
							<< ERR_HEADER
							<< c_argv[i]
							<< ERR_UNKNOWN_FLAG
							<< std::endl;
					break;
				}
			}
		}
		// Something else was given --> bad input.
		else
			_is_valid_input = false;

		// Increase argv counter.
		i++;
	}

	if (!_is_valid_input) std::cout
			<< ERR_HEADER
			<< ERR_INVALID_INPUT
			<< std::endl;
}


/*
 * Command parsing method:
 *    This method matches the input line with available commands,
 *    when user plays online.
 *
 *    Also this method returns boolean (true or false, is the game
 *    still running or not accordingly).
 *
 *    In this release you will exit the game only after 'exit' command
 *    was entered.
 */
bool Game::_parse_command(const std::string& cmd)
{
	size_t cmd_len = cmd.size();
	std::string answer;

	if (cmd_len == 0)
		return true;

	size_t delimiter_pos = cmd.find(" ");
	size_t found_save = cmd.find("save");
	size_t found_open = cmd.find("open");
	size_t found_tick = cmd.find("tick");
	size_t found_anim = cmd.find("animate");
	size_t found_help = cmd.find("help");
	size_t found_exit = cmd.find("exit");
	
	// Save command
	if ((found_save == 0) && ((delimiter_pos == 4) || (cmd_len == 4)))
	{
		if (cmd_len > 5)
		{
			_output_filename = cmd.substr(
					delimiter_pos + 1,
					cmd_len - delimiter_pos - 1);
			save();
		}
		else std::cout
				<< ERR_HEADER
				<< ERR_CMD_VALUE_EXPECTED
				<< std::endl;
	}
	// Open command
	else if ((found_open == 0) && ((delimiter_pos == 4) || (cmd_len == 4)))
	{
		if (cmd_len > 5)
		{
			if (!_debug)
				is_saved();

			_input_filename = cmd.substr(
					delimiter_pos + 1,
					cmd_len - delimiter_pos - 1);
			open();
		}
		else std::cout
				<< ERR_HEADER
				<< ERR_CMD_VALUE_EXPECTED
				<< std::endl;
	}
	// Tick command
	else if ((found_tick == 0) && ((delimiter_pos == 4) || (cmd_len == 4)))
	{
		if (cmd_len > 5)
		{
			_steps_limit = atoi((cmd.substr(
					delimiter_pos + 1,
					cmd_len - delimiter_pos - 1)).c_str());
			tick();
		}
		else std::cout
				<< ERR_HEADER
				<< ERR_CMD_VALUE_EXPECTED
				<< std::endl;
	}
	// Animate command
	else if (found_anim == 0 && ((delimiter_pos == 7) || (cmd_len == 7)))
	{
		if (cmd_len > 8)
		{
			_steps_limit = atoi((cmd.substr(
					delimiter_pos + 1,
					cmd_len - delimiter_pos - 1)).c_str());
			animate();
		}
		else std::cout
				<< ERR_HEADER
				<< ERR_CMD_VALUE_EXPECTED
				<< std::endl;
	}
	// Help command
	else if (found_help == 0 && cmd_len == 4)
	{
		help();
	}
	// Exit command
	else if (found_exit == 0 && cmd_len == 4)
	{
		if (!_debug)
			is_saved();

		return false; // Stop commands reading.
	}
	// Unknown command
	else std::cout
			<< ERR_HEADER
			<< ERR_UNKNOWN_COMMAND
			<< std::endl;

	return true; // Read the next command.
}

 
/*
 * Game saving method:
 *    This method writes game's universe into the specified
 *    input file.
 */
void Game::save()
{
	if (_debug) std::cout
			<< DBG_HEADER
			<< "Gonna save game to "
			<< _output_filename
			<< std::endl;

	_space->write_to_file(_output_filename);
	_saved = true;

	if (_debug) std::cout
			<< DBG_HEADER
			<< "Game was saved successfuly!"
			<< std::endl;
}


/*
 * Game opening method:
 *    This method restores the game from saved universe file.
 */
void Game::open()
{
	if (_debug) std::cout
			<< DBG_HEADER
			<< "Gonna open game from "
			<< _input_filename
			<< std::endl;

	delete _space; // Delete previous game.
	_space = new Universe(_input_filename);
}


/*
 * Game ticking method:
 *    This method makes 'universe moving' (calls 'do_step' method
 *    to Universe object) untill the steps limit will be reached.
 *
 *    At the end calls 'draw' method to Universe object.
 */
void Game::tick()
{
	if (_steps_limit > 0)
		_saved = false;

	for (int i = 0; i < _steps_limit; i++)
		_space->do_step();

	_space->draw();
}


/*
 * Game animating method:
 *    This method makes 'universe moving' (see also 'tick' method),
 *    but each step will be shown at the screen.
 */
void Game::animate()
{
	if (_steps_limit > 0)
		_saved = false;

	for (int i = 0; i < _steps_limit; i++)
	{
		_space->draw();
		_space->do_step();

		usleep(SLEEP_MSEC); // Call sleep function.

		system("clear"); // Call system clear screen function.
	}

	_space->draw();
}


/*
 * Game helping method:
 *    This method shows command help message at the game screen.
 */
void Game::help()
{
	std::cout
			<< HELP_COMMANDS
			<< std::endl;
}


/*
 * Game checking game save method:
 *    This method checks was the current game saved.
 *    If it was, then returns 'true', otherwise it asks
 *    confirming to not save current game.
 */
bool Game::is_saved()
{
	if (!_saved)
	{
		std::string answer;

		std::cout << MSG_NOT_SAVED_GAME;
		std::cin >> answer;

		while (answer != "yes" && answer != "no")
		{
			std::cout << MSG_YES_NO_ONLY;
			std::cin >> answer;
		}

		if (answer == "yes")
		{
			std::cout << MSG_WRITE_FILENAME;
			save();

			return true;
		}

		return false;
	}

	return true;
}


/* 
 * Game running method:
 *    This method runs the game if the program input was valid.
 *
 *    If user wants play online, then it starts the cycle,
 *    untill the commands are parsing.
 *
 *    If user specified offline mode, then it makes a number of steps
 *    iterations to Universe and saves the result into the output file.
 */
void Game::run()
{
	if (_debug) std::cout
			<< DBG_HEADER
			<< "The game is running!"
			<< std::endl;

	if (!_is_valid_input)
		return;

	// Online mode.
	if (_online)
	{
		bool is_running = true;
		std::string cmd_line;

		std::cout
				<< MSG_GREETING
				<< std::endl;

		while (is_running)
		{
			std::cout << CMD_IN;
			
			getline(std::cin, cmd_line);

			is_running = _parse_command(cmd_line);
		}
	}

	// Offline mode.
	else
	{
		if (_debug) std::cout
				<< DBG_HEADER
				<< "Offline gaming was started:\n"
				<< "    Opening from: " << _input_filename << "\n"
				<< "    Making steps: " << _steps_limit << "\n"
				<< "    Saving to:    " << _output_filename << "\n"
				<< std::endl;
		
		if (_debug)
		{
			std::cout
					<< DBG_HEADER
					<< "Before:"
					<< std::endl;

			_space->draw();
		}

		for (int i = 0; i < _steps_limit; i++)
			_space->do_step();

		if (_debug)
		{
			std::cout
					<< DBG_HEADER
					<< "After:"
					<< std::endl;

			_space->draw();
		}
		
		_space->write_to_file(_output_filename);
	}
}
#include "gamelogic.h"


bool is_flag(const std::string &line)
{
	return (line.size() == 2 && line[0] == '-');
}


bool is_argument(const std::string &line)
{
	return (line.size() > 2 && line[0] == '-' && line[1] == '-');
}


bool is_value(const std::string &line)
{
	return (!is_flag(line) && !is_argument(line));
}


Game::Game(int argc, char **argv)
{
	_debug = false;

	_online = true;
	_saved = true;
	_steps_limit = 0;
	_input_filename = std::string(STD_INPUT_FILENAME)
	_output_filename = std::string(STD_OUTPUT_FILENAME);

	_parse_input(argc, argv);

	_space = new Universe(_input_filename); // Open the universe from file.

	if (_debug) std::cout
			<< DBG_HEADER
			<< "Game was started with next properties:\n"
			<< "    debug:  " << _debug << "\n"
			<< "    online: " << _online << "\n"
			<< "    input:  " << _input_filename << "\n"
			<< "    output: " << _output_filename << "\n";
}


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


void Game::_parse_input(int argc, char **argv)
{
	int i;
	std::vector<std::string> c_argv;

	for (i = 0; i < argc; i++)
	{
		c_argv.push_back(std::string(argv[i]));

		if (c_argv[i] == "-d" || c_argv[i] == "--debug")
			_debug = true;
	}

	if (argc > 1 && is_value(c_argv[1])) // The saved game is specified at input as a value.
	{
		i = 2;
		_input_filename = std::string(argv[1]);
	}
	else // The saved game is not specified.
	{
		i = 1;
		_input_filename = std::string(STD_INPUT_FILENAME);
	}
	
	while (i < argc)
	{
		if (is_argument(c_argv[i])) // argument
		{
			if (_debug) std::cout
					<< DBG_HEADER
					<< "Argument parsing in development!"
					<< std::endl;
		}
		else if (is_flag(c_argv[i])) // flag
		{
			// TODO: Check is this condition works right!
			if ((c_argv[i][1] != 'h') 
				&& ((i + 1 < c_argc) && !is_value(c_argv[i + 1])))
			{
				std::cout
						<< ERR_HEADER
						<< ERR_NOT_ENOUGH_VALUES
						<< std::endl;
				break;
			}

			switch (c_argv[i][1])
			{
				case 'i':
				{
					// TODO: Remove if-condition from above
					if (i + 1 < argc) 
					_steps_limit = atoi(c_argv[++i]);
					_online = false;
					break;
				}
				case 'o':
				{
					_output_filename = c_argv[++i];
					break;
				}
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
					std::cout
							<< ERR_HEADER
							<< ERR_UNKNOWN_FLAG
							<< std::endl;
					break;
				}
			}
		}

		i++;
	}
}



bool Game::_parse_command(const std::string &cmd)
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
	
	if ((found_save == 0) && ((delimiter_pos == 4) || (cmd_len == 4)))
	{
		if (cmd_len > delimiter_pos)
		{
			_output_filename = cmd.substr(
					delimiter_pos + 1,
					cmd_len - delimiter_pos);
			save();
		}
		else std::cout
				<< ERR_HEADER
				<< ERR_VALUE_EXPECTED
				<< std::endl;
	}
	else if ((found_open == 0) && ((delimiter_pos == 4) || (cmd_len == 4)))
	{
		if (cmd_len > 5)
		{
			if (!_debug)
				is_saved();

			open(cmd.substr(
					delimiter_pos + 1,
					cmd_len - delimiter_pos));
		}
		else std::cout
				<< ERR_HEADER
				<< ERR_VALUE_EXPECTED
				<< std::endl;
	}
	else if ((found_tick == 0) && ((delimiter_pos == 4) || (cmd_len == 4)))
	{
		if (cmd_len > 5)
		{
			tick(atoi((cmd.substr(
					delimiter_pos + 1,
					cmd_len - delimiter_pos)).c_str())
			);
		}
		else std::cout
				<< ERR_HEADER
				<< ERR_VALUE_EXPECTED
				<< std::endl;
	}
	else if (found_anim == 0 && ((delimiter_pos == 7) || (cmd_len == 7)))
	{
		if (cmd_len > 7)
		{
			animate(atoi((cmd.substr(
					delimiter_pos + 1,
					cmd_len - delimiter_pos)).c_str())
			);
		}
		else std::cout
				<< ERR_HEADER
				<< ERR_VALUE_EXPECTED
				<< std::endl;
	}
	else if (found_help == 0 && cmd_len == 4)
	{
		help();
	}
	else if (found_exit == 0 && cmd_len == 4)
	{
		if (!_debug)
			is_saved();

		return false;
	}
	else std::cout
			<< ERR_HEADER
			<< ERR_UNKNOWN_COMMAND
			<< std::endl;

	return true;
}


bool Game::save()
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

	return true;
}


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


void Game::tick()
{
	if (_steps_limit > 0)
		_saved = false;

	for (int i = 0; i < _steps_limit; i++)
		_space->do_step();

	_space->draw();
}


void Game::animate()
{
	if (_steps_limit > 0)
		_saved = false;

	for (int i = 0; i < _steps_limit; i++)
	{
		_space->draw();
		_space->do_step();

		usleep(SLEEP_MSEC);

		system("clear");
	}

	_space->draw();
}


void Game::help()
{
	std::cout
			<< HELP_COMMANDS
			<< std::endl;
}


bool Game::is_saved()
{
	if (!_saved)
	{
		std::string answer;

		std::cout << NOT_SAVED_GAME;
		std::cin >> answer;

		while (answer != "yes" && answer != "no")
		{
			std::cout << WARNING_YES_NO_ONLY;
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


void Game::run()
{
	if (_debug) std::cout
			<< "The game is running!"
			<< std::endl;

	if (_online) // Online mode.
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

			is_running = _parse_line(cmd_line);
		}
	}
	else // Offline mode.
	{
		if (_debug) std::cout
				<< DBG_HEADER
				<< "Offline gaming was started:\n"
				<< "    Opening from: " << _input_filename << "\n"
				<< "    Making steps: " << _steps_limit << "\n"
				<< "    Saving to:    " << _output_filename << "\n"
		
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
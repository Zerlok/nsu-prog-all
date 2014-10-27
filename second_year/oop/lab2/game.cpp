#include "lifegame.h"


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

	if (_argc > 1 && is_value(_argv[1]))
	{
		_input_filename = _argv[1];
		_first_flag_num = 2;
	}
	else
	{
		_input_filename = STD_INPUT_FILENAME;
		_first_flag_num = 1;
	}


	if (_argc - _first_flag_num > 0) // There are more arguments.
	{
		_online = false; // offline mode.
		_parse_arguments();
	}
	else // There is only input file as argument.
	{
		_online = true; // online mode.
	}

	_space = new Universe(_input_filename); // openning the default universe.
	
	_saved = true;
	_output_filename = STD_OUTPUT_FILENAME;
	_line = "";

	#ifdef __DEBUG__
	std::cout << "The universe was opened from '" << _input_filename << "' file" << std::endl;
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
	std::cout << "Deleting space..." << std::endl;
	#endif
	delete _space;

	#ifdef __DEBUG__
	std::cout << "Done." << std::endl;
	#endif
}


void Game::_parse_arguments()
{
	int i = _first_flag_num;
	
	while (i < _argc)
	{
		if (is_argument(_argv[i])) // argument
		{
			#ifdef __DEBUG__
			std::cout << "Trying parse an argument: '" << _argv[i] << "'" << std::endl;
			#endif
			std::cout << "Parsing in development." << std::endl;
		}
		else if (is_flag(_argv[i])) // flag
		{
			if ((i + 1 >= _argc && _argv[i][1] != 'h')
				|| ((i + 1 < _argc) && !is_value(_argv[i + 1])))
			{
				std::cout << ERR_NOT_ENOUGH_VALUES << std::endl;
				break;
			}

			switch (_argv[i][1])
			{
				case 'i':
				{
					_steps_limit = atoi(_argv[i+1]);
					i++;
					break;
				}
				case 'o':
				{
					_output_filename = _argv[i+1];
					i++;
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



bool Game::_parse_line()
{
	std::string cmd(_line);
	size_t cmd_len = cmd.size();
	std::string answer;

	if (cmd_len == 0)
	{
		return true;
	}

	size_t delimiter_pos = cmd.find(" ");
	size_t found_save = cmd.find("save");
	size_t found_open = cmd.find("open");
	size_t found_tick = cmd.find("tick");
	size_t found_help = cmd.find("help");
	size_t found_exit = cmd.find("exit");
	
	if (found_save != std::string::npos)
	{
		if (delimiter_pos != std::string::npos && cmd_len > delimiter_pos)
		{
			_output_filename = _line.substr(delimiter_pos + 1, cmd_len - 1);
			save();
		}
		else
		{
			std::cout << ERR_NO_VALUE << std::endl;
		}
	}
	else if (found_open != std::string::npos)
	{
		if (delimiter_pos != std::string::npos && cmd_len > delimiter_pos)
		{
			_input_filename = _line.substr(delimiter_pos + 1, cmd_len - 1);

			#ifndef __DEBUG__
			is_saved();
			#endif

			open();
		}
		else
		{
			std::cout << ERR_NO_VALUE << std::endl;
		}
	}
	else if (found_tick != std::string::npos)
	{
		if (delimiter_pos != std::string::npos && cmd_len > delimiter_pos)
		{
			_steps_limit = atoi((_line.substr(delimiter_pos + 1, cmd_len - 1)).c_str());
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
		#ifndef __DEBUG__
		is_saved();
		#endif

		return false;
	}
	else
	{
		std::cout << ERR_UNKNOWN_COMMAND << std::endl;
	}

	return true;
}

bool Game::save()
{
	#ifdef __DEBUG__GAME__
	std::cout << "Gonna save game to " << _output_filename << std::endl;
	#endif

	_space->write_to_file(_output_filename);
	_saved = true;

	return true;
}


bool Game::open()
{
	#ifdef __DEBUG__GAME__
	std::cout << "Gonna open game from " << _input_filename << std::endl;
	#endif

	delete _space;
	_space = new Universe(_input_filename);

	return true;
}


bool Game::tick()
{
	if (_steps_limit > 0) _saved = false;

	for (int i = 0; i < _steps_limit; i++)
	{
		_space->draw();
		_space->do_step();

		usleep(SLEEP_MSEC);

		#ifndef __DEBUG__
		system("clear");
		#endif
	}

	_space->draw();

	return true;
}


void Game::help()
{
	std::cout << HELP_COMMANDS << std::endl;
}


bool Game::is_saved()
{
	#ifdef __DEBUG__GAME__
	std::cout << "Checking is saved..." << std::endl;
	#endif

	if (!_saved)
	{
		std::string answer;

		std::cout << WARNING_NOT_SAVED;
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
	if (_online) // Online mode.
	{
		bool is_running = true;
		// std::string cmd_line;

		std::cout << MSG_GREETING << std::endl;

		while (is_running)
		{
			std::cout << CMD_IN;
			getline(std::cin, _line);

			is_running = _parse_line();
		}
	}
	else // Offline mode.
	{
		#ifdef __DEBUG__GAME__
		std::cout << "Offline gaming started:" << std::endl;
		std::cout << "Opening from: " << _input_filename << std::endl;
		std::cout << "Making steps: " << _steps_limit << std::endl;
		std::cout << "Saving to: " << _output_filename << std::endl;
		#endif

		#ifdef __DEBUG__GAME__
		_space->draw();
		#endif

		for (int i = 0; i < _steps_limit; i++) _space->do_step();
		_space->write_to_file(_output_filename);

		#ifdef __DEBUG__GAME__
		_space->draw();
		#endif
	}
}
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// License:    GPL
// Author:     Brian K Preston
// File Name:  music_gui.cpp
// Build Date: Tue Dec 26 07:35:13 AM CST 2023
// Version:    0.0.1

#include <iostream>
#include <cstring>
#include <string>
#include <unistd.h>         /* for STDIN_FILENO */
#include <sys/select.h>     /* for pselect   */
#include <string>
#include <getopt.h>
#include "music_gui.hpp"

using namespace std;

const string VERSION_STRING = "0.0.1";
const int DEFAULT_ARGC = 2;
const unsigned short VERBOSE          = 0x01;
const unsigned short DEFAULTS         = 0x00;

static struct option long_options[] =
{
        {"verbose", no_argument, 0, 'v'},
        {"help", no_argument, 0, 'h'},
        {"version", no_argument, 0, 'r'},
};

unsigned short OPTION_FLAGS = DEFAULTS;

void print_version()
{
	cout << VERSION_STRING << endl;
}

void print_help()
{
	// cout	<< endl 
	// 		<< FMT_BOLD << FMT_FG_GREEN << "Usage: "            << FMT_RESET << endl
	// 		<< FMT_BOLD << FMT_FG_BLUE  << "split"              << FMT_RESET << " "
	// 		<< FMT_FG_BLUE              << "[-hvr][...]"        << FMT_RESET << " "
	// 		                            << "FILE [FILE2 ... ]" << FMT_RESET << " "
	// 															<<  endl << endl;
}

int parse_options(int argc, char* argv[])
{
	int opt = 0;
	int option_index = 0;
	optind = 0;
	while ((opt = getopt_long(argc, argv, "hvr", long_options, &option_index)) != -1)
	{
			switch (opt)
			{
			case 'h':
					print_help();
					return 0;
			case 'v':
					OPTION_FLAGS |= VERBOSE;
					break;
			case 'r':
					print_version();
					return 0;
			}
	}

	if (argc < DEFAULT_ARGC) // not correct number of args
	{
		cerr << "Expected argument after options, -h for help" << endl;
		return -1;
	}

	return 0;
}


int stdin_ready (int filedes)
{
	fd_set set;
	// declare/initialize zero timeout 
	struct timespec timeout = { .tv_sec = 0 };
	// initialize the file descriptor set
	FD_ZERO(&set);
	FD_SET(filedes, &set);
	// check stdin_ready is ready on filedes 
	return pselect(filedes + 1, &set, NULL, NULL, &timeout, NULL);
}

int main(int argc, char* argv[])
{
	try
	{
		if(stdin_ready(STDIN_FILENO))
		{
			std::string buffer;
			std::cin >> buffer;
			// add piped buffer to end of argv
			char* argvtmp[sizeof(char*) * argc+1];
			memcpy(argvtmp, argv, sizeof(char*) * argc);
			argvtmp[argc] = &buffer[0];
			argv = argvtmp;
			++argc;
		}
		return parse_options(argc, argv);
	}
	catch(std::logic_error& ex)
	{
	 	std::cout << ex.what() << std::endl;
	}
}

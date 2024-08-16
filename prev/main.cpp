#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

typedef short TERMCALL;

std::string fileHandling(int argc, char **argv)
{
	std::string inputString;
	std::fstream inputFile;

	if ( argc != 2 )
	{
		std::cout << "Input a filename!\n";
		exit(0);
	}

	inputString = argv[1];
	inputFile.open(inputString, std::ios_base::in);

	if ( inputFile.good() )
	{
		inputFile.close();
		return inputString;
	}
	else
	{
		std::ofstream outputFile;
		outputFile.open(inputString);
		outputFile.close();
		return inputString;
	}
}

TERMCALL handleEscapeCase(std::string inputString, int index)
{
	//newline
	if ( inputString[index + 1] == 'n' )
	{
		return 1;
	}
	//tab
	if ( inputString[index + 1] == 't' )
	{
		return 2;
	}
	//backspace
	if ( inputString[index + 1] == 'b' )
	{
		return 3;
	}
	//backslash
	if ( inputString[index + 1] == '\\' )
	{
		return 4;
	}
	//this will never run
	return 0;
}

TERMCALL handleSuperCase(std::string inputString, int index)
{
	//exit case
	if ( inputString[index + 1] == 'X' )
	{
		return 10;
	}
	return 0;
}

void terminal(std::string filename)
{
	std::fstream inputFile;
	inputFile.open(filename, std::ios_base::app | std::ios_base::in | std::ios_base::out);
	std::string inputString;
	TERMCALL _termcall = 0;

	while ( _termcall != 10 )
	{
		int index = 0;

		// Graphical Handling:
		system("clear");
		inputFile.seekg(0);
		std::cout << inputFile.rdbuf();
		std::cout << "\n\n\n\n\n\n";

		// Input Handling:
		std::cout << "$ ";
		std::getline(std::cin, inputString);

		while ( index < inputString.length() )
		{
			switch(inputString[index])
			{
				case '\\':
				_termcall = handleEscapeCase(inputString, index);
		        break;

		        case '^':
				_termcall = handleSuperCase(inputString, index);
				break;

		        default:
				inputFile << inputString[index];
		        _termcall = 0;
				break;
			}

			switch(_termcall)
			{
				/*
				TERMCALL Table:
				0 - append character
				1 - newline Character
				2 - tab Character
				3 - backspace 'Character'
				10 - exit
				*/

				case 1:
				inputFile << "\n";
				index++;
				break;

				case 2:
				inputFile << "\t";
				index++;
				break;

				case 3:
				inputFile << "\b\x00";
				index++;
				break;

				case 4:
				inputFile << "\\";
				index++;
				break;

				case 10: // EXITCODE
				inputFile.close();
				system("clear");
				exit(0);
				break;

				default:
				break;
			}
			index++;
		}
	}
}

int main(int argc, char **argv)
{
	std::string filename = fileHandling(argc, argv);
	terminal(filename);

	return 0;
}

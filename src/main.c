#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int file_error(char * filename)
{
	fprintf(stderr, "usage: %s <filename>\n", filename);
	return EXIT_FAILURE;
}

int validity_error(char * filename)
{
	fprintf(stderr, "the filename must not contain any of the following "
					"extraneous characters:\n"
					"[\\, /, -, .]\n");
	return EXIT_FAILURE;
}

int check_validity(char * filename)
{
	for ( int i = 0; i < strlen(filename); i++ )
	{
		switch(filename[i])
		{
			case '\\':
			case '/':
			case '-':
			case '.':
			return EXIT_FAILURE;
			break;

			default:
			break;
		}
	}
	return EXIT_SUCCESS;
}

int file_handling(int argc, char **argv)
{
	// if no filename
	if ( argc != 2 )
	{
		// non-segmentation fault code [optional ^_^]:
		// return file_error(argv[0]);

		file_error(argv[0]);
	}

	// if filename, check validity
	if ( check_validity(argv[1]) != EXIT_SUCCESS )
	{
		return validity_error(argv[1]);
	}
}

enum termcall
{
	// utilities
	nop = 0,
	save,
	write,
	quit,

	// characters
	tab,
	backspace,
};

enum termcall handle_escape_character(char * input,
									int current_character_index)
{
	switch(input[current_character_index + 1])
	{
		case '\\':
		return write;
		break;

		case 't':
		return tab;
		break;

		case 'b':
		return backspace;
		break;

		case 'q':
		return quit;
		break;

		case 's':
		return save;
		break;

		default:
		break;
	}
}

enum termcall handle_character_type(/*FILE * current_file, */ char * input)
{
	switch(input[0])
	{
		case '\\':
		return handle_escape_character(input, 0);
		break;

		default:
		return write;
		break;
	}
}

void hotmilk(char * filename)
{
	FILE * current_file = fopen(filename, "rw");

	if ( current_file == NULL )
	{
		printf("fopen() failed!");
		printf("creating file ...");

		current_file = fopen(filename, "w");
	}

	enum termcall current_termcall = nop;

	char * user_input = (char *)malloc(1024 * sizeof(char));

	while ( current_termcall != quit )
	{
		// go to start of file
		rewind(current_file);
		// clear screen
		//system("clear");
		// output file
		int current_character; // of type int to handle EOF case
		while ( (current_character = fgetc(current_file)) != EOF )
			putchar(current_character);
		// arbitrary spacer
		printf("\n\n\n\n\n");
		// output shell prompt
		system("echo -n $(whoami)"); printf("@hotmilk $ ");
		// get user input
		user_input = scanf("%s", user_input);

		for ( int i = 0; i < strlen(user_input); i++ )
		{
			current_termcall = handle_character_type
								(/*current_file*/ user_input);

			switch(current_termcall)
			{
				case save:
				fflush(current_file);
				printf("saving file!\n");
				break;

				case write:
				fwrite(user_input, sizeof(char), 1, current_file);
				printf("writing to file!\n");
				break;

				case quit:
				fclose(current_file);
				current_termcall = quit;
				printf("quit statement\n");
				break;

				default:
				break;
			}
		}
		printf("reached end of termcall loop!\n");
	}
}

int main(int argc, char **argv)
{
	int exit_code = file_handling(argc, argv);

	if ( exit_code == EXIT_FAILURE ) { return EXIT_FAILURE; }

	char * filename = (char *)malloc(strlen(argv[1]) * sizeof(char));
	filename = argv[1];
	hotmilk(filename);
	return 0;
}

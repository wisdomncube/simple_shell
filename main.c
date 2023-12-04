#include "shell.h"

/**
 * main - entry point of application
 * @argc: number of arguments
 * @argv: array of arguments
 * Return: 0 for success
 */

int main(int argc, char *argv[])
{
	char command[128];

	while (1)
	{
		char *comm;

		if (argc > 0)
		{
			enter_command();
			comm = user_input(argv[0], command, sizeof(command));
		}
		else
			printf("Enter file to run");

		if (comm != NULL)
		{
			printf("entered command %s\n", comm);
			execute_command(comm);
		}
	}
	return (0);
}

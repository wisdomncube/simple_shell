#include "shell.h"

/**
 * user_input - takes in command entered by user
 * @command: command entered by user
 * @size: size of the command
 * @executable: name of file running
 * Return: return correctly entered command
 */

char *user_input(char *executable, char *command, size_t size)
{
	char *exec_comm = NULL;

	command = fgets(command, size, stdin);

	if (command == NULL)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
			perror("fgets");
			exit(EXIT_FAILURE);
		}
	}
	if (command != NULL)
	{
		if (strncmp(command, "/bin/", 4) != 0)
		{
			printf("%s: No such file or directory\n", executable);
		}
		if (strncmp(command, "/bin/", 4) == 0 && strchr(command, ' ')
		    != NULL)
		{
			printf("%s: No such file or directory\n", executable);
		}
		if (strncmp(command, "/bin/", 4) == 0 && strchr(command, ' ')
		    == NULL)
		{
			exec_comm = command;
		}
	}
	command[strcspn(command, "\n")] = '\0';
	return (exec_comm);
}

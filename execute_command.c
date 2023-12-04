#include "shell.h"

/**
 * execute_command - Executes a command.
 * @command: Command to execute.
 */

void execute_command(char *command)
{
	char *args[2];
	pid_t child_pid = fork();

	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (child_pid == 0)
	{
		args[0] = command;
		args[1] = NULL;

		execve(args[0], args, NULL);
	}
	else
	{
		int status;
		pid_t executed_command = waitpid(child_pid, &status, 0);

		if (executed_command == -1)
		{
			perror("waitpid");
			exit(EXIT_FAILURE);
		}
		if (WIFEXITED(status))
			printf("Child process exited with status: %d\n",
			       WEXITSTATUS(status));
		else
			printf("Child process did not terminate normally\n");
	}
}

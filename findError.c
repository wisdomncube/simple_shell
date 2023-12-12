#include "shell.h"

/**
 * findError - calls the error according the builtin, syntax or permission
 * @datash: data structure that contains arguments
 * @eval: error value
 * Return: error
 */
int findError(shellData *datash, int eval)
{
	char *error;

	switch (eval)
	{
	case -1:
		error = errorEnv(datash);
		break;
	case 126:
		error = errorPath(datash);
		break;
	case 127:
		error = errorNotFound(datash);
		break;
	case 2:
		if (_strcmp("exit", datash->args[0]) == 0)
			error = errorExitShellProgram(datash);
		else if (_strcmp("cd", datash->args[0]) == 0)
			error = errorGetCD(datash);
		break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		free(error);
	}

	datash->status = eval;
	return (eval);
}

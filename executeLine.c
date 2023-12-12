#include "shell.h"

/**
 * executeLine - finds builtins and commands
 *
 * @datash: data relevant (args)
 * Return: 1 on success.
 */
int executeLine(shellData *datash)
{
	int (*builtin)(shellData *datash);

	if (datash->args[0] == NULL)
		return (1);

	builtin = getBuiltIn(datash->args[0]);

	if (builtin != NULL)
		return (builtin(datash));

	return (executeCommand(datash));
}

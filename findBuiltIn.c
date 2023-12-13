#include "shell.h"

/**
 * getBuiltIn - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */
int (*getBuiltIn(char *cmd))(shellData *)
{
	builtinCommands builtin[] = {
		{ "exit", exitShellProgram },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; builtin[i].name; i++)
	{
		if (_strcmp(builtin[i].name, cmd) == 0)
			break;
	}

	return (builtin[i].f);
}

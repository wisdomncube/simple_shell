#include "shell.h"

/**
 * changeDir - changes current directory
 *
 * @datash: data relevant
 * Return: 1 on success
 */
int changeDir(shellData *datash)
{
	char *dir;
	int ishome, ishome2, isddash;

	dir = datash->args[1];

	if (dir != NULL)
	{
		ishome = _strcmp("$HOME", dir);
		ishome2 = _strcmp("~", dir);
		isddash = _strcmp("--", dir);
	}

	if (dir == NULL || !ishome || !ishome2 || !isddash)
	{
		changeDirToHome(datash);
		return (1);
	}

	if (_strcmp("-", dir) == 0)
	{
		changeDirPrev(datash);
		return (1);
	}

	if (_strcmp(".", dir) == 0 || _strcmp("..", dir) == 0)
	{
		changeDirDot(datash);
		return (1);
	}

	changeDirTo(datash);

	return (1);
}

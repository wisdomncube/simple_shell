#include "shell.h"

/**
 * readLine - reads the input string.
 *
 * @i_eof: return value of getline function
 * Return: input string
 */
char *readLine(int *i_eof)
{
	char *input = NULL;
	size_t bufsize = 0;

	*i_eof = getline(&input, &bufsize, stdin);

	return (input);
}

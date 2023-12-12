#include "shell.h"

/**
 * noComment - deletes comments from the input
 *
 * @in: input string
 * Return: input without comments
 */
char *noComment(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}

	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}

	return (in);
}

/**
 * shellStartingPoint - Loop of shell
 * @datash: data relevant (av, input, args)
 *
 * Return: no return.
 */
void shellStartingPoint(shellData *datash)
{
	int loop, i_eof;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "$ ", 2);
		input = readLine(&i_eof);
		if (i_eof != -1)
		{
			input = noComment(input);
			if (input == NULL)
				continue;

			if (findSyntaxError(datash, input) == 1)
			{
				datash->status = 2;
				free(input);
				continue;
			}
			input = replaceVariable(input, datash);
			loop = tokenizeCommands(datash, input);
			datash->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

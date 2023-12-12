#include "shell.h"

/**
 * swapCharacter - swaps | and & for non-printed chars
 *
 * @input: input string
 * @bool: type of swap
 * Return: swapped string
 */
char *swapCharacter(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * addNodes - add separators and command lines in the lists
 *
 * @head_s: head of separator list
 * @head_l: head of command lines list
 * @input: input string
 * Return: no return
 */
void addNodes(listSeparator **head_s, commandList **head_l, char *input)
{
	int i;
	char *line;

	input = swapCharacter(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			addSeparatorNodeEnd(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			addSeparatorNodeEnd(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = swapCharacter(line, 1);
		addLineNodeEnd(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * nextNode - go to the next command line stored
 *
 * @list_s: separator list
 * @list_l: command line list
 * @datash: data structure
 * Return: no return
 */
void nextNode(listSeparator **list_s, commandList **list_l, shellData *datash)
{
	int loop_sep;
	listSeparator *ls_s;
	commandList *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (datash->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * tokenizeCommands - splits command lines according to
 * the separators ;, | and &, and executes them
 *
 * @datash: data structure
 * @input: input string
 * Return: 0 to exit, 1 to continue
 */
int tokenizeCommands(shellData *datash, char *input)
{

	listSeparator *head_s, *list_s;
	commandList *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	addNodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		datash->input = list_l->line;
		datash->args = splitLine(datash->input);
		loop = executeLine(datash);
		free(datash->args);

		if (loop == 0)
			break;

		nextNode(&list_s, &list_l, datash);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	freeListSeparator(&head_s);
	freeCommandList(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

/**
 * splitLine - tokenizes the input string
 *
 * @input: input string.
 * Return: string splitted.
 */
char **splitLine(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _reallocdp(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

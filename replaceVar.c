#include "shell.h"

/**
 * checkEnviron - checks if the typed variable is an env variable
 *
 * @h: head of linked list
 * @in: input string
 * @data: data structure
 * Return: no return
 */
void checkEnviron(rVar **h, char *in, shellData *data)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = data->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				addRVarNode(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	addRVarNode(h, j, NULL, 0);
}

/**
 * checkVars - check if the typed variable is $$ or $?
 *
 * @h: head of the linked list
 * @in: input string
 * @st: last status of the Shell
 * @data: data structure
 * Return: no return
 */
int checkVars(rVar **h, char *in, char *st, shellData *data)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				addRVarNode(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				addRVarNode(h, 2, data->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				addRVarNode(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				addRVarNode(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				addRVarNode(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				addRVarNode(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				addRVarNode(h, 0, NULL, 0);
			else
				checkEnviron(h, in + i, data);
		}
	}

	return (i);
}

/**
 * replacedInput - replaces string into variables
 *
 * @head: head of the linked list
 * @input: input string
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: replaced string
 */
char *replacedInput(rVar **head, char *input, char *new_input, int nlen)
{
	rVar *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * replaceVariable - calls functions to replace string into vars
 *
 * @input: input string
 * @datash: data structure
 * Return: replaced string
 */
char *replaceVariable(char *input, shellData *datash)
{
	rVar *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = auxItoa(datash->status);
	head = NULL;

	olen = checkVars(&head, input, status, datash);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = replacedInput(&head, input, new_input, nlen);

	free(input);
	free(status);
	freeRVarList(&head);

	return (new_input);
}

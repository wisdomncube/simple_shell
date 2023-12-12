#include "shell.h"

/**
 * addRVarNode - adds a variable at the end
 * of a rVar list.
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
rVar *addRVarNode(rVar **head, int lvar, char *val, int lval)
{
	rVar *new, *temp;

	new = malloc(sizeof(rVar));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}

/**
 * freeRVarList - frees a rVar list
 * @head: head of the linked list.
 * Return: no return.
 */
void freeRVarList(rVar **head)
{
	rVar *temp;
	rVar *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

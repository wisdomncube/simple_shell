#include "shell.h"

/**
 * addSeparatorNodeEnd - adds a separator found at the end
 * of a listSeparator.
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
listSeparator *addSeparatorNodeEnd(listSeparator **head, char sep)
{
	listSeparator *new, *temp;

	new = malloc(sizeof(listSeparator));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
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
 * freeListSeparator - frees a listSeparator
 * @head: head of the linked list.
 * Return: no return.
 */
void freeListSeparator(listSeparator **head)
{
	listSeparator *temp;
	listSeparator *curr;

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

/**
 * addLineNodeEnd - adds a command line at the end
 * of a commandList.
 * @head: head of the linked list.
 * @line: command line.
 * Return: address of the head.
 */
commandList *addLineNodeEnd(commandList **head, char *line)
{
	commandList *new, *temp;

	new = malloc(sizeof(commandList));
	if (new == NULL)
		return (NULL);

	new->line = line;
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
 * freeCommandList - frees a commandList
 * @head: head of the linked list.
 * Return: no return.
 */
void freeCommandList(commandList **head)
{
	commandList *temp;
	commandList *curr;

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

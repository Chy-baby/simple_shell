#include "main.h"

/**
 * add_Snode_end - adds a separator found at the end
 * @head: head of the linked list.
 * @sep: separator found (; | &).
 * Return: address of the head.
 */
S_list_t *add_Snode_end(S_list_t **head, char sep)
{
	S_list_t *new, *temp;

	new = malloc(sizeof(S_list_t));
	if (new == NULL)
		return (NULL);

	new->separate = sep;
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
 * free_Slist - frees the linked list
 * @head: linked list head
 * Return: nothing
 */
void free_Slist(S_list_t **head)
{
	S_list_t *temp;
	S_list_t *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_Lnode_end - add a cmd line at the end of the list
 * @head: head
 * @line: cmd line.
 * Return: returns address of the head
 */
L_list *add_Lnode_end(L_list **head, char *line)
{
	L_list *new, *temp;

	new = malloc(sizeof(L_list));
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
 * free_Llist - frees a line_list
 * @head: head
 * Return: nothing
 */
void free_Llist(L_list **head)
{
	L_list *temp;
	L_list *current;

	if (head != NULL)
	{
		current = *head;
		while ((temp = current) != NULL)
		{
			current = current->next;
			free(temp);
		}
		*head = NULL;
	}
}

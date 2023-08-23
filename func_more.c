#include "main.h"

/**
 * add_v - adds a variable at the end
 * @head: head of the linked list.
 * @lvar: length of the variable.
 * @val: value of the variable.
 * @lval: length of the value.
 * Return: address of the head.
 */
r_var_t *add_v(r_var_t **head, int lvar, char *val, int lval)
{
	r_var_t *new, *temp;

	new = malloc(sizeof(r_var_t));
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
 * free_rvar - free the  list
 * @head: head
 * Return: no return.
 */
void free_rvar(r_var_t **head)
{
	r_var_t *temp;
	r_var_t *current;

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

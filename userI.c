#include "main.h"

/**
 * envCheck - function that checks whether
 * a typed variable is an env variable
 * @head: head of linked list
 * @input: input string
 * @data: data structure
 * Return: no return
 */

void envCheck(r_var_t **head, char *input, data *data)
{
	char **env;
	int chr;
	int i;
	int row;
	int lval;

	env = data->Environ;
	for (row = 0; env[row]; row++)
	{
		for (i = 1, chr = 0; env[row][chr]; chr++)
		{
			if (env[row][chr] == '=')
			{
				lval = strLen(env[row] + chr + 1);
				add_v(head, i, env[row] + chr + 1, lval);
				return;
			}

			if (input[i] == env[row][chr])
				i++;
			else
				break;
		}
	}

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ' ' || input[i] == '\t'
				|| input[i] == ';' || input[i] == '\n')
			break;
	}

	add_v(head, i, NULL, 0);
}


/**
 * varsCheck - checking if the input is $$ or $?
 * @h: head of the linked list
 * @data: data structure
 * @in: input
 * @st: last status
 * Return: no return
 */

int varsCheck(r_var_t **h, char *in, char *st, data *data)
{
	int i;
	int sts;
	int pd;

	sts = strLen(st);
	pd = strLen(data->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_v(h, 2, st, sts), i++;
			else if (in[i + 1] == '$')
				add_v(h, 2, data->pid, pd), i++;
			else if (in[i + 1] == '\n')
				add_v(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_v(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_v(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_v(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_v(h, 0, NULL, 0);
			else
				envCheck(h, in + i, data);
		}
	}

	return (i);
}


/**
 * replacedInput - function that replace
 * string into variables
 * @input: input string
 * @head: head of the linked list
 * @new_input: new input string (replaced)
 * @nlen: new length
 * Return: returns replaced string
 */

char *replacedInput(r_var_t **head, char *input, char *new_input, int nlen)
{
	r_var_t *index;
	int i, j, k;

	index = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(index->len_var) && !(index->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (index->len_var && !(index->len_val))
			{
				for (k = 0; k < index->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < index->len_val; k++)
				{
					new_input[i] = index->val[k];
					i++;
				}
				j += (index->len_var);
				i--;
			}
			index = index->next;
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
 * repVar - functions to replace string
 * @input:string
 * @runtime_data: data structure
 * Return: replaced string
 */

char *repVar(char *input, data *runtime_data)
{
	r_var_t *head, *index;
	char *status, *new_input;
	int Oldlen, Newlen;

	status = intTostr(runtime_data->status);
	head = NULL;

	Oldlen = varsCheck(&head, input, status, runtime_data);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	index = head;
	Newlen = 0;

	while (index != NULL)
	{
		Newlen += (index->len_val - index->len_var);
		index = index->next;
	}

	Newlen += Oldlen;

	new_input = malloc(sizeof(char) * (Newlen + 1));
	new_input[Newlen] = '\0';

	new_input = replacedInput(&head, input, new_input, Newlen);

	free(input);
	free(status);
	free_rvar(&head);

	return (new_input);
}

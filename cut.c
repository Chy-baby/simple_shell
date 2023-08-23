#include "main.h"

/**
 * swap - function that swaps & and |
 * @bool: swap type
 * @input:string
 * Return: returns swapped string
 */

char *swap(char *input, int bool)
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
if (input[i] == 16)
input[i] = '|';
if (input[i] == 12)
{
input[i] = '&';
}
}
}
return (input);
}


/**
 * addNodes - function that add separators and cmd line
 * @s_head: head of separator list
 * @c_head: head of command lines list
 * @input: input string
 * Return: no return
 */

void addNodes(S_list_t **s_head, L_list **c_head, char *input)
{
	int i;
	char *line;

	input = swap(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			add_Snode_end(s_head, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			add_Snode_end(s_head, input[i]);
			i++;
		}
	}

	line = strTok(input, ";|&");
	do {
		line = swap(line, 1);
		add_Lnode_end(c_head, line);
		line = strTok(NULL, ";|&");
	} while (line != NULL);

}


/**
 * next - moves to the next cmd line stored
 * @listS: separator list
 * @runtime_data: data structure
 *@listL: cmd line list
 * Return: no return
 */

void next(S_list_t **listS, L_list **listL, data *runtime_data)
{
	S_list_t *ls_s;
	int loop_s;
	L_list *ls_l;

	loop_s = 1;
	ls_s = *listS;
	ls_l = *listL;

	while (ls_s != NULL && loop_s)
	{
		if (runtime_data->status == 0)
		{
			if (ls_s->separate == '&' || ls_s->separate == ';')
				loop_s = 0;
			if (ls_s->separate == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separate == '|' || ls_s->separate == ';')
				loop_s = 0;
			if (ls_s->separate == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_s)
			ls_s = ls_s->next;
	}

	*listS = ls_s;
	*listL = ls_l;
}

/**
 * sptLine - token of the input string
 * @input:string
 * Return:token string
 */

char **sptLine(char *input)
{
	size_t i;
	size_t bufsize;
	char **tokens;
	char *token;

	bufsize = TOKEN_BUFFER_SIZE;
	tokens = malloc(sizeof(char *) * (bufsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation failed\n", 18);
		exit(EXIT_FAILURE);
	}

	token = strTok(input, TOKEN_DELIMITERS);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bufsize)
		{
			bufsize += TOKEN_BUFFER_SIZE;
			tokens = Reallocdp(tokens, i, sizeof(char *) * bufsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = strTok(NULL, TOKEN_DELIMITERS);
		tokens[i] = token;
	}

	return (tokens);
}

/**
 * splitcmd - splits command lines given by
 * the separators ;, | and &, and run them
 * @input: input string
 * @runtime_data: data structure
 * Return: 0 to exit otherwise  1
 */

int splitcmd(data *runtime_data, char *input)
{
	int loop;

	S_list_t *head_s, *list_s;
	L_list *head_l, *list_l;

	head_s = NULL;
	head_l = NULL;

	addNodes(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		runtime_data->info = list_l->line;
		runtime_data->args = sptLine(runtime_data->info);
		loop = exec_line(runtime_data);
		free(runtime_data->args);

		if (loop == 0)
			break;

		next(&list_s, &list_l, runtime_data);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_Slist(&head_s);
	free_Llist(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}

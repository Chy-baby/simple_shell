#include "main.h"

/**
 * no_comment - deletes users  comments
 * @n:string
 * Return: output with no  comments
 */

char *no_comment(char *n)
{
	int i;
	int j;

	j = 0;
	for (i = 0; n[i]; i++)
	{
		if (n[i] == '#')
		{
			if (i == 0)
			{
				free(n);
				return (NULL);
			}
			if (n[i - 1] == ' ' || n[i - 1] == '\t' || n[i - 1] == ',')
				j = i;

		}
	}
	if (j != 0)
	{
		n = Realloc(n, i, j + 1);
		n[j] = '\0';
	}
	return (n);
}


/**
 * sh_loop - a Loop
 * @runtime_data: data relevant
 * Return: nothing
 */

void sh_loop(data *runtime_data)
{
	int i;
	int j;
	char *input;

	i = 1;
	while (i == 1)
	{
		write(STDIN_FILENO, "#cisfun$ ", 9);
		input = readLine(&j);
		if (j != -1)
		{
			input = no_comment(input);
			if (input == NULL)
				continue;
			if (check_syntax_err(runtime_data, input) == 1)
			{
				runtime_data->status = 2;
				free(input);
				continue;
			}
			input = repVar(input, runtime_data);
			i = splitcmd(runtime_data, input);
			runtime_data->count += 1;
			free(input);
		}
		else
		{
			i = 0;
			free(input);
		}
	}
}

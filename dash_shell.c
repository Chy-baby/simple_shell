#include "main.h"

/**
 * rep_c - keeps track on the repetitions of a char
 * @i: index
 * @input: string
 * Return: repetitions
 */
int rep_c(char *input, int i)
{
	if (*(input - 1) == *input)
		return (rep_c(input - 1, i + 1));

	return (i);
}

/**
 * error_rep - looks for syntax errors
 * @input:string
 * @i: index
 * @last: last char
 * Return:returns 0 when there are no errors
 */
int error_rep(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (error_rep(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = rep_c(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = rep_c(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (error_rep(input + 1, i + 1, *input));
}

/**
 * firstC - looks for index of the first char
 * @input:string
 * @i: index
 * Return: returns 1 if there is an error, 0 in other case.
 */
int firstC(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 *syntax_err - looks for syntax error
 * @input: input string
 * @runtime_data: data structure
 * @i: index
 * @bool: a boolean
 * Return: nothing
 */
void syntax_err(data *runtime_data, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *err, *count;
	int len;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error found: \"";
	msg3 = "\" unexpected\n";
	count = intTostr(runtime_data->count);
	len = strLen(runtime_data->argv[0]) + strLen(count);
	len += strLen(msg) + strLen(msg2) + strLen(msg3) + 2;

	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(count);
		return;
	}
	strCpy(err, runtime_data->argv[0]);
	strCat(err, ": ");
	strCat(err, count);
	strCat(err, msg2);
	strCat(err, msg);
	strCat(err, msg3);
	strCat(err, "\0");

	write(STDERR_FILENO, err, len);
	free(err);
	free(count);
}

/**
 * check_syntax_err - function to find a syntax error
 * @runtime_data:structure
 * @input:string
 * Return: 1 if there is an error otherwise 0
 */
int check_syntax_err(data *runtime_data, char *input)
{
	int start = 0;
	int _char = 0;
	int i = 0;

	_char = firstC(input, &start);
	if (_char == -1)
	{
		syntax_err(runtime_data, input, start, 0);
		return (1);
	}

	i = error_rep(input + start, 0, *(input + start));
	if (i != 0)
	{
		syntax_err(runtime_data, input, start + i, 1);
		return (1);
	}

	return (0);
}

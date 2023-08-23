#include "main.h"

/**
 * cmpEnv - compares env varibles names with output
 * @namenv: name of the env variable
 * @name: name input
 * Return: 0 if are not equal. Another value if they are
 */

int cmpEnv(const char *namenv, const char *name)
{
	int i;

	for (i = 0; namenv[i] != '='; i++)
	{
		if (namenv[i] != name[i])
			return (0);
	}
	return (i + 1);
}

/**
 * Env - prints the env variables
 * @runtime_data: data
 * Return: returns 1 if no error
 * is found
 */

int Env(data *runtime_data)
{
	int i;
	int j;

	for (i = 0; runtime_data->Environ[i]; i++)
	{
		for (j = 0; runtime_data->Environ[i][j]; j++)
			;
		write(STDOUT_FILENO, runtime_data->Environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	runtime_data->status = 0;
	return (1);
}

/**
 * getEnv - gets an env variable
 * @_environ: env variable
 * @name: name of the env variables
 * Return:return value of the env variables otherwise NULL
 */

char *getEnv(const char *name, char **_environ)
{
	char *ptr;
	int i;
	int  j;

	ptr = NULL;
	j = 0;

	for (i = 0; _environ[i]; i++)
	{
		j = cmpEnv(_environ[i], name);
		if (j)
		{
			ptr = _environ[i];
			break;
		}
	}
	return (ptr + j);
}


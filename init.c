#include "main.h"

/**
 * c_info - takes  copies of info
 * using it to create a new env
 * @value: value
 * @name: name
 * Return: new env
 */

char *c_info(char *name, char *value)
{
	int len_name;
	int len;
	int len_value;
	char *new;

	len_name = strLen(name);
	len_value = strLen(value);
	len = len_name + len_value + 2;
	new = malloc(sizeof(char) * (len));
	strCpy(new, name);
	strCat(new, "=");
	strCat(new, value);
	strCat(new, "\0");
	return (new);
}


/**
* set_Env - sets an environment variable
 * @name: name of the environment variable
 * @value: value of the environment variable
 * @runtime_data: data structure (environ)
 * Return: no return
 */

void set_Env(char *name, char *value, data *runtime_data)
{
	int i;
	char *var_env, *name_env;

	for (i = 0; runtime_data->Environ[i]; i++)
	{
		var_env = strdUp(runtime_data->Environ[i]);
		name_env = strTok(var_env, "=");
		if (strCmp(name_env, name) == 0)
		{
			free(runtime_data->Environ[i]);
			runtime_data->Environ[i] = c_info(name_env, value);
			free(var_env);
			return;
		}
		free(var_env);
	}

	runtime_data->Environ = Reallocdp(runtime_data->Environ, i,
			sizeof(char *) * (i + 2));
	runtime_data->Environ[i] = c_info(name, value);
	runtime_data->Environ[i + 1] = NULL;
}


/**
 * setenv_c -compares env variables names
 * @runtime_data: data relevant
 * Return: 1 on success.
 */

int setenv_c(data *runtime_data)
{

	if (runtime_data->args[1] == NULL || runtime_data->args[2] == NULL)
	{
		getError(runtime_data, -1);
		return (1);
	}
	set_Env(runtime_data->args[1], runtime_data->args[2], runtime_data);

	return (1);
}


/**
 * unsetEnv - function that deletes a environment variable
 * @runtime_data: data relevant (env name)
 * Return: 1 on success.
 */

int unsetEnv(data *runtime_data)
{
	char **realloc_env, *var_env;
	char *name_env;
	int i;
	int  k, j;

	if (runtime_data->args[1] == NULL)
	{
		getError(runtime_data, -1);
		return (1);
	}
	k = -1;
	for (i = 0; runtime_data->Environ[i]; i++)
	{
		var_env = strdUp(runtime_data->Environ[i]);
		name_env = strTok(var_env, "=");
		if (strCmp(name_env, runtime_data->args[1]) == 0)
		{
			k = i;
		}
		free(var_env);
	}
	if (k == -1)
	{
		getError(runtime_data, -1);
		return (1);
	}
	realloc_env = malloc(sizeof(char *) * (i));
	for (i = j = 0; runtime_data->Environ[i]; i++)
	{
		if (i != k)
		{
			realloc_env[j] = runtime_data->Environ[i];
			j++;
		}
	}
	realloc_env[j] = NULL;
	free(runtime_data->Environ[k]);
free(runtime_data->Environ);
runtime_data->Environ = realloc_env;
return (1);
}


#include "main.h"


/**
 * err_path - prints error message  path and failure denied permission
 * @runtime_data: data
 *
 * Return:returns error string.
 */
char *err_path(data *runtime_data)
{
	int len;
	char *str;
	char *err;

	str = intTostr(runtime_data->count);
	len = strLen(runtime_data->argv[0]) + strLen(str);
	len += strLen(runtime_data->args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}
	strCpy(err, runtime_data->argv[0]);
	strCat(err, ": ");
	strCat(err, str);
	strCat(err, ": ");
	strCat(err, runtime_data->args[0]);
	strCat(err, ": Permissions denied\n");
	strCat(err, "\0");
	free(str);
	return (err);
}



/**
 * err_env - function that prints  error message for env in get_env.
 * @runtime_data: data relevant
 * Return: returns error message.
 */
char *err_env(data *runtime_data)
{
	int len;
	char *err;
	char *str;
	char *err_msg;

	str = intTostr(runtime_data->count);
	err_msg = ": Cannot add or remove things from the environment.\n";
	len = strLen(runtime_data->argv[0]) + strLen(str);
	len += strLen(runtime_data->args[0]) + strLen(err_msg) + 4;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(err);
		free(str);
		return (NULL);
	}



	strCpy(err, runtime_data->argv[0]);
	strCat(err, ": ");
	strCat(err, str);
	strCat(err, ": ");
	strCat(err, runtime_data->args[0]);
	strCat(err, err_msg);
	strCat(err, "\0");
	free(str);

	return (err);
}

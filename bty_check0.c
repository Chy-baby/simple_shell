#include "main.h"

/**
 * strCatCd - function that concatenates the message for cd check
 *
 * @runtime_data: Relevant data (counter, arguments) for the runtime.
 * @err_msg:err message to print
 * @err: msg output
 * @str: lines
 * Return: error message
 */
char *strCatCd(data *runtime_data, char *err_msg, char *err, char *str)
{

	char *Iflag;

	strCpy(err, runtime_data - > argv[0]);
	strCat(err, ": ");
	strCat(err, str);
	strCat(err, ": ");
	strCat(err, runtime_data->args[0]);
	strCat(err, err_msg);
	if (runtime_data->args[1][0] == '-')
	{
		Iflag = malloc(3);
		Iflag[0] = '-';
		Iflag[1] = runtime_data->args[1][1];
		Iflag[2] = '\0';
		strCat(err, Iflag);
		free(Iflag);
	}
	else
	{
		strCat(err, runtime_data->args[1]);
	}

	strCat(err, "\n");
	strCat(err, "\0");
	return (err);
}

/**
 * err_cd - error msg for cd cmd
 * @runtime_data: Relevant data (counter, arguments) for the runtime.
 * Return: error message
 */
char *err_cd(data *runtime_data)
{
	char *err;
	int len;
	int lenId;
	char *str;
	char *err_msg;

	str = intTostr(runtime_data->count);
	if (runtime_data->args[1][0] == '-')
	{
		err_msg = ": option not allowed ";
		lenId = 2;
	}
	else
	{
		err_msg = ": can not change dir to ";
		lenId = strLen(runtime_data->args[1]);
	}

	len = strLen(runtime_data->argv[0]) + strLen(runtime_data->args[0]);
	len += strLen(str) + strLen(err_msg) + lenId + 5;
	err = malloc(sizeof(char) * (len + 1));

	if (err == 0)
	{
		free(str);
		return (NULL);
	}

	err = strCatCd(runtime_data, err_msg, err, str);

	free(str);

	return (err);
}

/**
 * error_not_found- error message when cmd is not found
 * @runtime_data: Relevant data (counter, arguments) for the runtime.
 * Return: error message
 */
char *error_not_found(data *runtime_data)
{
	int len;
	char *err;
	char *str;

	str = intTostr(runtime_data->count);
	len = strLen(runtime_data->argv[0]) + strLen(str);
	len += strLen(runtime_data->args[0]) + 16;
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
	strCat(err, ": not found\n");
	strCat(err, "\0");
	free(str);
	return (err);
}

/**
 *err_exit_msg -  error messages exiting within the context of the function.
 * @runtime_data: Relevant data (counter, arguments) for the runtime.
 * Return:error message
 */
char *err_exit_msg(data runtime_data)
{
	int len;
	char *err;
	char *str;

	str = intTostr(runtime_data->count);
	len = strLen(runtime_data->argv[0]) + strLen(str);
	len += strLen(runtime_data->args[0]) + strLen(runtime_data->args[1]) + 23;
	err = malloc(sizeof(char) * (len + 1));
	if (err == 0)
	{
		free(str);
		return (NULL);
	}
	strCpy(err, runtime_data->argv[0]);
	strCat(err, ": ");
	strCat(err, str);
	strCat(err, ": ");
	strCat(err, runtime_data->args[0]);
	strCat(err, ":number not allowed: ");
	strCat(err, runtime_data->args[1]);
	strCat(err, "\n\0");
	free(str);

	return (err);
}

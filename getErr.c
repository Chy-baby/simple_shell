#include "main.h"

/**
 * getError -function calls the error according to the arg,
 * @runtime_data: data structure
 * @err_v: valueof errors
 * Return: returns  error
 */

int getError(data *runtime_data, int err_v)
{
	char *error;

	switch (err_v)
	{
				case 127:
			error = error_not_found(runtime_data);
			break;
		case -1:
			error = err_env(runtime_data);
			break;
		case 126:
			error = err_path(runtime_data);
			break;

		case 2:
			if (strCmp("exit", runtime_data->args[0]) == 0)
				error = err_exit_msg(runtime_data);
			else if (strCmp("cd", runtime_data->args[0]) == 0)
				error = err_cd(runtime_data);
			break;
	}

	if (error)
	{
		write(STDERR_FILENO, error, strLen(error));
		free(error);
	}

	runtime_data->status = err_v;
	return (err_v);
}

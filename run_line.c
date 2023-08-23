#include "main.h"

/**
 * exec_line - function that finds builtins and commands
 * @runtime_data: data relevant (args)
 * Return: 1 on success
 */

int exec_line(data *runtime_data)
{
	int (*builtin)(data *runtime_data);

	if (runtime_data->args[0] == NULL)
		return (1);
	builtin = getBuiltinf(runtime_data->args[0]);
	if (builtin != NULL)
		return (builtin(runtime_data));
	return (exec_cmd(runtime_data));
}

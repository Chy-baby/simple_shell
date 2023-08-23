#include "main.h"

/**
 * Help - display builtin help message
 * @runtime_data: data structure
 * Return: Always 0
 */

int Help(data *runtime_data)
{
	if (runtime_data->args[1] == 0)
		Help_general();
	else if (strCmp(runtime_data->args[1], "setenv") == 0)
		HelpSetEnv();
	else if (strCmp(runtime_data->args[1], "env") == 0)
		HelpEnv();
	else if (strCmp(runtime_data->args[1], "unsetenv") == 0)
		helpUnsetEnv();
	else if (strCmp(runtime_data->args[1], "help") == 0)
		HelpS();
	else if (strCmp(runtime_data->args[1], "exit") == 0)
		Help_exit();
	else if (strCmp(runtime_data->args[1], "cd") == 0)
		Help_cd();
	else if (strCmp(runtime_data->args[1], "alias") == 0)
		Help_alias();
	else
		write(STDERR_FILENO, runtime_data->args[0],
		      strLen(runtime_data->args[0]));

	runtime_data->status = 0;
	return (1);
}

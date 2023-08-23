#include "main.h"

/**
 * cd_sh - changes current directory
 * @runtime_data: data
 * Return: 1 on success
 */
int cd_sh(data *runtime_data)
{
	char *directory;
	int home, home2, nhome;

	directory = runtime_data->args[1];

	if (directory  != NULL)
	{
		home = strCmp("$HOME", directory);
		home2 = strCmp("~", directory);
		nhome = strCmp("--", directory);
	}

	if (directory == NULL || !home || !home2 || !nhome)
	{
		cd_home(runtime_data);
		return (1);
	}

	if (strCmp("-", directory) == 0)
	{
		cd_pre(runtime_data);
		return (1);
	}

	if (strCmp(".", directory) == 0 || strCmp("..", directory) == 0)
	{
		cdDot(runtime_data);
		return (1);
	}

	cdTo(runtime_data);

	return (1);
}

#include "main.h"

/**
 * getBuiltinf - builtin that pais the command in the arg
 * @cmd: command
 * Return: function pointer of the builtin command
 */

int (*getBuiltinf(char *cmd))(data *)
{
	int Env(data *);
int Exit(data *);
int setenv_c(data *);
int unsetEnv(data *);
int cd_sh(data *);
int Help(data *);
	cmdArgs_t cmdArg[] = {
		{ "env", Env },
		{ "exit", Exit},
		{ "setenv", setenv_c },
		{ "unsetenv", unsetEnv },
		{ "cd", cd_sh },
		{ "help", Help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; cmdArg[i].name; i++)
	{
		if (strCmp(cmdArg[i].name, cmd) == 0)
			break;
	}

	return (cmdArg[i].f);
}

#include "main.h"

/**
 * dataF - frees data structure
 * @runtime_data: data structure
 * Return: no return
 */

void dataF(data *runtime_data)
{
	size_t i;

	for (i = 0; runtime_data->Environ[i]; i++)

	{
		free(runtime_data->Environ[i]);
	}
	free(runtime_data->Environ);
	free(runtime_data->pid);
}

/**
 * dataS - Initialize data structure
 * @runtime_data: data structure
 * @argv: argument vector
 * Return: no return
 */

void dataS(data *runtime_data, char **argv)
{

	size_t i;

	runtime_data->argv = argv;

	runtime_data->info = NULL;
	runtime_data->args = NULL;
	runtime_data->status = 0;
	runtime_data->count = 1;

	for (i = 0; environ[i]; i++)
		;
	runtime_data->Environ = malloc(sizeof(char *) * (i + 1));
	for (i = 0; environ[i]; i++)
	{
		runtime_data->Environ[i] = strdUp(environ[i]);
	}
	runtime_data->Environ[i] = NULL;
	runtime_data->pid = intTostr(getpid());
}

/**
 * main - where compilation starts
 * @argc: main argument for counting
 * @argv: main argument vector which is an array
 * Return: 0 on success.
 */

int main(int argc, char **argv)
{
	data runtime_data;
	(void) argc;

	signal(SIGINT, getSigint);
	dataS(&runtime_data, argv);
	sh_loop(&runtime_data);
	dataF(&runtime_data);
	if (runtime_data.status < 0)
		return (255);
	return (runtime_data.status);
}

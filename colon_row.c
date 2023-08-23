#include "main.h"

/**
 * cdir - checks ":" if is in the current directory.
 * @path:ptr
 * @i:int
 * Return: 1 if the path is searchable in the cd, 0 otherwise.
 */
int cdir(char *path, int *i)
{
	if (path[*i] == ':')
		return (1);

	while (path[*i] != ':' && path[*i])
	{
		*i += 1;
	}

	if (path[*i])
		*i += 1;

	return (0);
}

/**
 * locates - locates a command
 *
 * @cmd: command name
 * @_environ: environment variable
 * Return: location of the command.
 */
char *locates(char *cmd, char **_environ)
{
	char *path, *ptr_path, *token_path, *dir;
	int len_dir, len_cmd, i;
	struct stat st;

	path = getEnv("PATH", _environ);
	if (path)
	{
		ptr_path = strdUp(path);
		len_cmd = strLen(cmd);
		token_path = strTok(ptr_path, ":");
		i = 0;
		while (token_path != NULL)
		{
			if (cdir(path, &i))
				if (stat(cmd, &st) == 0)
					return (cmd);
			len_dir = strLen(token_path);
			dir = malloc(len_dir + len_cmd + 2);
			strCpy(dir, token_path);
			strCat(dir, "/");
			strCat(dir, cmd);
			strCat(dir, "\0");
			if (stat(dir, &st) == 0)
			{
				free(ptr_path);
				return (dir);
			}
			free(dir);
			token_path = strTok(NULL, ":");
		}
		free(ptr_path);
		if (stat(cmd, &st) == 0)
			return (cmd);
		return (NULL);
	}
	if (cmd[0] == '/')
		if (stat(cmd, &st) == 0)
			return (cmd);
	return (NULL);
}

/**
 * Executes - determines if is an executable
 * @runtime_data: data structure
 * Return: 0 if is not an executable, other number if it does
 */
int Executes(data *runtime_data)
{
	struct stat st;
	int i;
	char *input;

	input = runtime_data->args[0];
	for (i = 0; input[i]; i++)
	{
		if (input[i] == '.')
		{
			if (input[i + 1] == '.')
				return (0);
			if (input[i + 1] == '/')
				continue;
			else
				break;
		}
		else if (input[i] == '/' && i != 0)
		{
			if (input[i + 1] == '.')
				continue;
			i++;
			break;
		}
		else
			break;
	}
	if (i == 0)
		return (0);

	if (stat(input + i, &st) == 0)
	{
		return (i);
	}
	getError(runtime_data, 127);
	return (-1);
}

/**
 * error_cmd - verifies if user has permissions to access
 *
 * @dir: destination directory
 * @runtime_data: data structure
 * Return: 1 if there is an error, 0 if not
 */
int error_cmd(char *dir, data *runtime_data)
{
	if (dir == NULL)
	{
		getError(runtime_data, 127);
		return (1);
	}

	if (strCmp(runtime_data->args[0], dir) != 0)
	{
		if (access(dir, X_OK) == -1)
		{
			getError(runtime_data, 126);
			free(dir);
			return (1);
		}
		free(dir);
	}
	else
	{
		if (access(runtime_data->args[0], X_OK) == -1)
		{
			getError(runtime_data, 126);
			return (1);
		}
	}

	return (0);
}

/**
 * exec_cmd - executes command lines
 * @runtime_data: data relevant
 * Return: 1 on success.
 */
int exec_cmd(data *runtime_data)
{
	pid_t pid;
	pid_t wpid;
	int state;
	int exe;
	char *dir;
	(void) wpid;

	exe = Executes(runtime_data);
	if (exe == -1)
		return (1);
	if (exe == 0)
	{
		dir = locates(runtime_data->args[0], runtime_data->Environ);
		if (error_cmd(dir, runtime_data) == 1)
			return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (exe == 0)
			dir = locates(runtime_data->args[0], runtime_data->Environ);
		else
			dir = runtime_data->args[0];
		execve(dir + exe, runtime_data->args, runtime_data->Environ);
	}
	else if (pid < 0)
	{
		perror(runtime_data->argv[0]);
		return (1);
	}
	else
	{
		do {
			wpid = waitpid(pid, &state, WUNTRACED);
		} while (!WIFEXITED(state) && !WIFSIGNALED(state));
	}

	runtime_data->status = state / 256;
	return (1);
}

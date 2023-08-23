#include "main.h"

/**
 * cdDot - changes to the directory
 * @runtime_data: data relevant
 * Return: no return
 */
void cdDot(data *runtime_data)
{
	char pwd[PATH_MAX];
	char *dir, *cpPwd, *cp_tok_pwd;

	getcwd(pwd, sizeof(pwd));
	cpPwd = strdUp(pwd);
	set_Env("OLDPWD", cpPwd, runtime_data);
	dir = runtime_data->args[1];
	if (strCmp(".", dir) == 0)
	{
		set_Env("PWD", cpPwd, runtime_data);
		free(cpPwd);
		return;
	}
	if (strCmp("/", cpPwd) == 0)
	{
		free(cpPwd);
		return;
	}
	cp_tok_pwd = cpPwd;
	rev_str(cp_tok_pwd);
	cp_tok_pwd = strTok(cp_tok_pwd, "/");
	if (cp_tok_pwd != NULL)
	{
		cp_tok_pwd = strTok(NULL, "\0");

		if (cp_tok_pwd != NULL)
			rev_str(cp_tok_pwd);
	}
	if (cp_tok_pwd != NULL)
	{
		chdir(cp_tok_pwd);
		set_Env("PWD", cp_tok_pwd, runtime_data);
	}
	else
	{
		chdir("/");
		set_Env("PWD", "/", runtime_data);
	}
	runtime_data->status = 0;
	free(cpPwd);
}

/**
 * cdTo - changes to a directory
 * @runtime_data: data relevant
 * Return: nothing
 */
void cdTo(data *runtime_data)
{
	char pwd[PATH_MAX];
	char *cp_pwd;
	char *dir;
	char *cpDir;

	getcwd(pwd, sizeof(pwd));

	dir = runtime_data->args[1];
	if (chdir(dir) == -1)
	{
		getError(runtime_data, 2);
		return;
	}

	cp_pwd = strdUp(pwd);
	set_Env("OLDPWD", cp_pwd, runtime_data);

	cpDir = strdUp(dir);
	set_Env("PWD", cpDir, runtime_data);

	free(cp_pwd);
	free(cpDir);

	runtime_data->status = 0;

	chdir(dir);
}

/**
 * cd_pre - changes to the last dir
 * @runtime_data: data relevant
 * Return: no return
 */
void cd_pre(data *runtime_data)
{
	char pwd[PATH_MAX];
	char *p_pwd, *p_oldpwd, *cp_pwd, *cp_oldpwd;

	getcwd(pwd, sizeof(pwd));
	cp_pwd = strdUp(pwd);

	p_oldpwd = getEnv("OLDPWD", runtime_data->Environ);

	if (p_oldpwd == NULL)
		cp_oldpwd = cp_pwd;
	else
		cp_oldpwd = strdUp(p_oldpwd);

	set_Env("OLDPWD", cp_pwd, runtime_data);

	if (chdir(cp_oldpwd) == -1)
		set_Env("PWD", cp_pwd, runtime_data);
	else
		set_Env("PWD", cp_oldpwd, runtime_data);

	p_pwd = getEnv("PWD", runtime_data->Environ);

	write(STDOUT_FILENO, p_pwd, strLen(p_pwd));
	write(STDOUT_FILENO, "\n", 1);

	free(cp_pwd);
	if (p_oldpwd)
		free(cp_oldpwd);

	runtime_data->status = 0;

	chdir(p_pwd);
}

/**
 * cd_home - changes to home dir
 * @runtime_data: data relevant
 * Return: no return
 */
void cd_home(data *runtime_data)
{
	char *p_pwd;
	char  *home;
	char pwd[PATH_MAX];

	getcwd(pwd, sizeof(pwd));
	p_pwd = strdUp(pwd);

	home = getEnv("HOME", runtime_data->Environ);

	if (home == NULL)
	{
		set_Env("OLDPWD", p_pwd, runtime_data);
		free(p_pwd);
		return;
	}

	if (chdir(home) == -1)
	{
		getError(runtime_data, 2);
		free(p_pwd);
		return;
	}

	set_Env("OLDPWD", p_pwd, runtime_data);
	set_Env("PWD", home, runtime_data);
	free(p_pwd);
	runtime_data->status = 0;
}

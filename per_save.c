#include "main.h"


/**
 * HelpSetEnv - information on  builtin setenv
 * Return: no return
 */
void HelpSetEnv(void)
{

	char *help = "setenv: setenv (const char *name, const char *value,";

	write(STDOUT_FILENO, help, strLen(help));
	help = "int replace)\n\t";
	write(STDOUT_FILENO, help, strLen(help));
	help = "Adds new definition \n";
	write(STDOUT_FILENO, help, strLen(help));
}
/**
 * helpUnsetEnv - information on builtin unsetenv
 * Return: no return
 */
void helpUnsetEnv(void)
{
	char *help = "unsetenv: unsetenv (const char *name)\n\t";

	write(STDOUT_FILENO, help, strLen(help));
	help = "Remove an entry completely \n";
	write(STDOUT_FILENO, help, strLen(help));
}


/**
 * Help_general -help information for the help builtin
 * Return: no return
 */
void Help_general(void)
{
	char *help = "This section explains using the help feature\n";

	write(STDOUT_FILENO, help, strLen(help));
	help = "If needed, provide more info. use 'help' for details.";
	write(STDOUT_FILENO, help, strLen(help));
	help = "Try 'help name' for more infomation on 'name'.\n\n ";
	write(STDOUT_FILENO, help, strLen(help));
	help = "[args]]\n  setenv: setenv [variable] [value]  unsetenv: \n ";
	write(STDOUT_FILENO, help, strLen(help));
	help = "setenv: setenv [variable] [value]\nunsetenv: unsetenv [variable] \n";
	write(STDOUT_FILENO, help, strLen(help));
	write(STDOUT_FILENO, help, strLen(help));
	help = " alias: alias name cd [-L|[-P [-e]] [-@]] [dir] ";
	write(STDOUT_FILENO, help, strLen(help));
	help = "exit: exit [n]\nenv: env [option] [name=value] [command [args]] \n ";

}
/**
 * Help_exit -information on the buiLt in exit
 * Return: no return
 */
void Help_exit(void)
{
	char *help = "exit:goodbye user \n";

	write(STDOUT_FILENO, help, strLen(help));
	help = "Exits the shell with n,if n is not found then exit";
	write(STDOUT_FILENO, help, strLen(help));
	help = "status is of the last command\n";
	write(STDOUT_FILENO, help, strLen(help));
}
/**
 * HelpEnv - Help information for the builtin env
 * Return: no return
 */
void HelpEnv(void)
{
	char *Help = "env: env [option] [name=value] [command [args]]\n\t";

	write(STDOUT_FILENO, Help, strLen(Help));
	Help = "Print enviroment.\n";
	write(STDOUT_FILENO, Help, strLen(Help));

}

#include "main.h"

/**
 * HelpS - Help information on builtin help.
 * Return: no return
 */
void HelpS(void)
{
	char *help = "help: help [-dms] [pattern ...]\n";

	write(STDOUT_FILENO, help, strLen(help));
	help = "\tinformation on builtin commands.\n ";
	write(STDOUT_FILENO, help, strLen(help));
	help = "summaries ON builtin commands.\n";
	write(STDOUT_FILENO, help, strLen(help));
}
/**
 * Help_alias -information ON builtin alias.
 * Return: no return
 */
void Help_alias(void)
{
	char *help = "alias: alias [-p] [name[=value]...]\n";

	write(STDOUT_FILENO, help, strLen(help));
	help = "\tdisplay aliases.\n ";
	write(STDOUT_FILENO, help, strLen(help));
}
/**
 * Help_cd -information on builtin alias.
 * Return: no return
 */
void Help_cd(void)
{
	char *help = "cd: cd [-L|[-P [-e]] [-@]] [dir]\n";

	write(STDOUT_FILENO, help, strLen(help));
	help = "\tChange  working directory.\n ";
	write(STDOUT_FILENO, help, strLen(help));
}

#include "main.h"

/**
 * getSigint - Handle the crtl + c call in prompt
 * @s:signal handler
 */

void getSigint(int s)
{
	(void)s;
	write(STDOUT_FILENO, "\ngoodbye\n", 11);
	 exit(EXIT_SUCCESS);
}

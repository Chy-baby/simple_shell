#include "main.h"
/**
 * readLine - reads users input
 * @eof: return value of getline()
 * Return:a string
 */
char *readLine(int *eof)
{
	char *input = NULL;
	size_t bufsize = 0;
	*eof = getline(&input, &bufsize, stdin);
	return (input);
}

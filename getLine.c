#include "main.h"

/**
 * Bline -  assigns  line var for get_line
 * @lineptr: Buffer that store the input str
 * @buf: str that is been called to line
 * @n: size of line
 * @j: size of buffer
 */

void Bline(char **lineptr, size_t *n, char *buf, size_t j)
{
	if (*lineptr == NULL)
	{
		if (j > BUFFER_SIZE)
			*n = j;
		else
			*n = BUFFER_SIZE;
		*lineptr = buf;
	}
	else if (*n < j)
	{
		if (j > BUFFER_SIZE)
			*n = j;
		else
			*n = BUFFER_SIZE;
		*lineptr = buf;
	}
	else
	{
		strCpy(*lineptr, buf);
		free(buf);
	}
}



/**
 * getLine - Function that read input from stream
 * @lineptr: buffer that stores the input
 * @stream: stream been read from
 * @n: size if lineptr
 * Return: returns number of byte
 */

ssize_t getLine(char **lineptr, size_t *n, FILE *stream)
{
	int i;
	static ssize_t input;
	ssize_t r_val;
	char *buf;
	char j = 'z';

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (buf == 0)
		return (-1);
	while (j != '\n')
	{
		i = read(STDIN_FILENO, &j, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buf);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFFER_SIZE)
			buf = Realloc(buf, input, input + 1);
		buf[input] = j;
		input++;
	}
	buf[input] = '\0';
	Bline(lineptr, n, buf, input);
	r_val = input;
	if (i != 0)
		input = 0;
	return (r_val);
}

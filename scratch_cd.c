#include "main.h"




/**
 * strToint -function that converts a str to an int
 * @s: input
 * Return: integer.
 */
int strToint(char *s)
{
	unsigned int counter = 0, i;
	unsigned int  size = 0, l = 0, n = 1, m = 1;

	while (*(s + counter) != '\0')
	{
		if (size > 0 && (*(s + counter) < '0' || *(s + counter) > '9'))
			break;

		if (*(s + counter) == '-')
			n *= -1;

		if ((*(s + counter) >= '0') && (*(s + counter) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		counter++;
	}

	for (i = counter - size; i < counter; i++)
	{
		l = l + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (l * n);
}

/**
 * intTostr - function that convert int to string.
 * @nt:input
 * Return: String.
 */
char *intTostr(int nt)
{
	unsigned int i;
	int lenght = getLength(nt);
	char *buf;

	buf = malloc(sizeof(char) * (lenght + 1));
	if (buf == 0)
		return (NULL);

	*(buf + lenght) = '\0';

	if (nt < 0)
	{
		i = nt * -1;
		buf[0] = '-';
	}
	else
	{
		i = nt;
	}

	lenght--;
	do {
		*(buf + lenght) = (nt % 10) + '0';
		i = i / 10;
		lenght--;
	}
	while (i > 0)
		;
	return (buf);
}

/**
 * getLength - function that gets lenght of a number
 * @x:an integer
 * Return:returns Lenght of the number
 */
int getLength(int x)
{
	unsigned int i;
	int len = 1;

	if (x < 0)
	{
		len++;
		i = x * -1;
	}
	else
	{
		i = x;
	}
	while (i > 9)
	{
		len++;
		i = i / 10;
	}

	return (len);
}

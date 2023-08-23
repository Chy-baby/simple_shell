#include "main.h"

/**
 * strdUp - duplicates a str in the heap memory.
 * @s: Type char pointer str
 * Return: duplicated str
 */
char *strdUp(const char *s)
{
	char *new;
	size_t len;

	len = strLen(s);
	new = malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	memCpy(new, s, len + 1);
	return (new);
}

/**
 * strLen - Returns the lenght of a string.
 * @s: Type char pointer
 * Return: Always 0.
 */
int strLen(const char *s)
{
	int len;

	for (len = 0; s[len] != 0; len++)
	{
	}
	return (len);
}

/**
 * cmpChars - compare chars of strings
 * @str: input string.
 * @dem: delimiter.
 *
 * Return: 1 if are equals, 0 if not.
 */
int cmpChars(char str[], const char *dem)
{
	size_t  x, y, z;

	for (x = 0, z = 0; str[x]; x++)
	{
		for (y = 0; dem[y]; y++)
		{
			if (str[x] == dem[y])
			{
				z++;
				break;
			}
		}
	}
	if (x == z)
		return (1);
	return (0);
}

/**
 * strTok - Slipt  strings
 * @str:string being split
 * @dem: delimiter to look for
 *
 * Return:slipted string
 */
char *strTok(char str[], const char *dem)
{
	char *strBeg;
	static char *split;
	static char *strEnd;
	size_t i;
	unsigned int bool;

	if (str != NULL)
	{
		if (cmpChars(str, dem))
			return (NULL);
		split = str;
		i = strLen(str);
		strEnd = &str[i];
	}
	strBeg = split;
	if (strBeg == strEnd)
		return (NULL);

	for (bool = 0; *split; split++)
	{
		if (split != strBeg)
			if (*split && *(split - 1) == '\0')
				break;
		for (i = 0; dem[i]; i++)
		{
			if (*split == dem[i])
			{
				*split = '\0';
				if (split == strBeg)
					strBeg++;
				break;
			}
		}
		if (bool == 0 && *split)
			bool = 1;
	}
	if (bool == 0)
		return (NULL);
	return (strBeg);
}

/**
 * isDigit - checking if string passed is a num
 * @s:string
 * Return: returns 1 if string is a num , 0 in otherwise
 */
int isDigit(const char *s)
{
	unsigned int i;

	for (i = 0; s[i]; i++)
	{
		if (s[i] < 48 || s[i] > 57)
			return (0);
	}
	return (1);
}

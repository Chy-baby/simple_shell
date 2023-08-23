#include "main.h"

/**
 * strSpn - gets the length of a prefix substring.
 * @s: initial segment.
 * @vaild: accepted bytes.
 * Return: the number of accepted bytes.
 */
int strSpn(char *s, char *vaild)
{
	int i, j, bool;

	for (i = 0; *(s + i) != '\0'; i++)
	{
		bool = 1;
		for (j = 0; *(vaild + j) != '\0'; j++)
		{
			if (*(s + i) == *(vaild + j))
			{
				bool = 0;
				break;
			}
		}
		if (bool == 1)
			break;
	}
	return (i);
}

/**
 * strCat - join two strings
 * @des:destination char array for the concatenated string
 * @src: const char array, which is the source string
 * Return:returns the destination
 */
char *strCat(char *des, const char *src)
{
	int i;
	int j;

	for (i = 0; des[i] != '\0'; i++)
	{
		;
	}
	for (j = 0; src[j] != '\0'; j++)
	{
		des[i] = src[j];
		i++;
	}

	des[i] = '\0';
	return (des);
}

/**
 * strCmp - Function that compares two strings.
 * @first: type str compared
 * @second: type str compared
 * Return: returns 0.
 */
int strCmp(char *first, char *second)
{
	int i;

	for (i = 0; first[i] == second[i] && first[i]; i++)
		;

	if (first[i] > second[i])
		return (1);
	if (first[i] < second[i])
		return (-1);
	return (0);
}
/**
 * strChr - checks a character in a string
 * @str: string
 * @c: character
 * Return:returns first occurrence of the c.
 */
char *strChr(char *str, char c)
{
	unsigned int i = 0;

	for (; *(str + i) != '\0'; i++)
		if (*(str + i) == c)
			return (str + i);
	if (*(str + i) == c)
		return (str + i);
	return ('\0');
}

/**
 * strCpy - function that Copy  strings
 * @des:pointer to  the des of the copied string
 * @src:pointer to the source of str
 * Return: the des
 */
char *strCpy(char *des, char *src)
{

	size_t a;

	for (a = 0; src[a] != '\0'; a++)
	{
		des[a] = src[a];
	}
	des[a] = '\0';

	return (des);
}

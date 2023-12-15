#include "main.h"

/**
 * _strlen - Return number of characters (except '\0') in a given string
 * @s: The string whose length is returned
 *
 * Return: The length of s
 */
size_t _strlen(char *s)
{
	size_t len = 0;

	while (s != NULL && *s)
	{
		len++;
		s++;
	}
	return (len);
}

/**
 * _strchr - Returns a pointer to the first instance of a char in a string
 * @str: The str which is iterated
 * @c: The character which is searched for in str
 *
 * Return: A pointer to the first instance of c in str (NULL if c not in str)
 */
char *_strchr(char *str, char c)
{
	while (str && *str)
	{
		if (*str == c)
		{
			return (str);
		}
		str++;
	}
	return (NULL);
}

/**
 * _strcmp - Compares two given strings and returns an appropriate int
 * @s1: First string
 * @s2: Second string
 *
 * Return: an int greater than, less than, or equal to 0, if s1 > s2,
 * s1 < s2, or s1 == s2 respectively
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 - *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}

/**
 * _strtok - Splits a given string with a given delimiter
 * @str: string to be split
 * @delim: The delimiter used to split the string
 *
 * Return: array consisting of parts of str that are separated by the delim
 */
char **_strtok(char *str, char *delim)
{
	unsigned int i = 0, j = 0, token_found = 0;
	char **strarr;

	strarr = malloc(sizeof(char *));
	if (strarr != NULL)
		strarr[i] = malloc(sizeof(char));
	while (strarr != NULL && strarr[i] != NULL && *str)
	{
		if (_strchr(delim, *str) == NULL)
		{
			token_found = 1;
			strarr[i][j] = *str;
			j++;
			strarr[i] = _realloc(strarr[i], sizeof(char) * (j),
					     sizeof(char) * (j + 1));
		}
		else if (token_found)
		{
			token_found = 0;
			strarr[i][j] = '\0';
			i++;
			j = 0;
			strarr = _realloc(strarr, sizeof(char *) * (i),
					  sizeof(char *) * (i + 1));
			if (strarr != NULL)
				strarr[i] = malloc(sizeof(char));
		}
		str++;
	}
	if (token_found)
	{
		strarr[i][j] = '\0';
		i++;
		strarr = _realloc(strarr, sizeof(char *) * (i),
				  sizeof(char *) * (i + 1));
	}
	else
		free(strarr[i]);
	strarr[i] = NULL;
	return (strarr);
}

/**
 * _strcat - Concatenates two strings and returns  pointer to the result
 * @num: amount of strings to concatenate
 *
 *
 * Return: A pointer to the dest string
 */
char *_strcat(int num, ...)
{
	int i = 0, j = 0;
	unsigned int k;
	va_list ap;
	char *cat = malloc(1);
	char *str;

	va_start(ap, num);
	while (i < num)
	{
		str = va_arg(ap, char *);
		cat = _realloc(cat, j + 1, j + _strlen(str) + 1);
		for (k = 0; k < _strlen(str); k++)
		{
			cat[j] = str[k];
			j++;
		}
		i++;
	}
	cat[j] = '\0';
	return (cat);
}

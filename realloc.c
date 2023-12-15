#include <stdlib.h>
#include "main.h"

/**
 * get_min - Returns the minimum of two non negative integers
 * @n1: First number
 * @n2: Second number
 *
 * Return: Minimum of n1 and n2
 */
unsigned int get_min(unsigned int n1, unsigned int n2)
{
	if (n1 <= n2)
	{
		return (n1);
	}
	return (n2);
}

/**
 * _realloc - Implementation of realloc using malloc and free
 * @ptr: The address of previously allocated memory
 * @old_size: Amount of memory previously allocated to ptr
 * @new_size: Amount of memory to reallocate to ptr
 *
 * Return: The newly allocated space
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	char *new_ptr;
	char *old_ptr;

	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		return ((void *) new_ptr);
	}
	if (ptr != NULL && new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	if (old_size == new_size)
	{
		return (ptr);
	}
	new_ptr = malloc(new_size);
	old_ptr = (char *) ptr;
	if (new_ptr != NULL)
	{
		for (i = 0; i < get_min(old_size, new_size); i++)
		{
			new_ptr[i] = old_ptr[i];
		}
		free(ptr);
	}
	return ((void *) new_ptr);
}

/**
 * free_arr - Frees memory allocated for array of pointers to allocated memory
 * @arr: The array to be freed
 *
 * Return: void
 */
void free_arr(char **arr)
{
	char **ptr;

	ptr = arr;
	while (ptr != NULL && *ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}
	free(arr);
}

/**
 * free_strs - Frees memory allocated for a variable number of strings
 * @n: The number of memory areas to free
 *
 * Return: void
 */
void free_strs(int n, ...)
{
	int i = 0;
	va_list ap;
	char *str;

	va_start(ap, n);
	while (i < n)
	{
		str = va_arg(ap, char *);
		free(str);
		i++;
	}
}

/**
 * free_if_malloced - Frees the command path used to execute a command if it
 * has been malloced
 * @c_path: The command path
 * @arg: The actual command retrieved from stdin
 *
 * Return: void
 */
void free_if_malloced(char *c_path, char *arg)
{
	if (_strchr(arg, '/') == NULL)
		free(c_path);
}

#include "main.h"

/**
 * _strcpy - Copies string in second argument to the first argument
 * @dest: string to be copied into
 * @src: string being copied
 *
 * Return: pointer to the resulting string
 */
char *_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

/**
 * pow_ten - caluculate ten raised to a number
 * @n: number input
 *
 * Return: result
 */
unsigned int pow_ten(unsigned int n)
{
	int res = 1;

	while (n > 0)
	{
		res *= 10;
		n--;
	}
	return (res);
}
/**
 * num_to_str - convert unsigned int to string
 * @num: converted number
 *
 * Return: string output
 */
char *num_to_str(unsigned int num)
{
	unsigned int len = 1, i = 0;
	unsigned int tmp = num;
	char *str;

	while (tmp / 10)
	{
		len++;
		tmp /= 10;
	}
	str = malloc(len + 1);
	len--;
	while (len >= 1)
	{
		int n = num / pow_ten(len);

		str[i] = n + '0';
		num -= n * pow_ten(len);
		i++;
		len--;
	}
	str[i] = (num % 10) + '0';
	str[i + 1] = '\0';
	return (str);
}

/**
 * _memcpy - memcpy implementation
 * @dest: destination
 * @src: source
 * @n: number of bytes to copy
 *
 * Return: pointer to dest
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		*(dest + i) = src[i];
	}
	return (dest);
}

/**
 * getline_multi - Extension of getline function for multiple lines
 * @line_buffer: Pointer to the mem area where the input is stored
 * @buff_size: Pointer to an int holding the size allocated to line_buffer
 *
 * Return: buff_size
 */
int getline_multi(char **line_buffer, size_t *buff_size)
{
	char *buffer = malloc(1);
	int line_size = 0;

	buffer[0] = '\0';
	while (line_size >= 0)
	{
		line_size = getline(line_buffer, buff_size, stdin);
		if (line_size >= 0)
		{
			char *ptr = buffer;

			buffer = _strcat(2, buffer, *line_buffer);
			free(ptr);
		}
		else
			free(*line_buffer);
	}
	*line_buffer = buffer;
	return (*buff_size);
}

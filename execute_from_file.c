#include "main.h"
#include <string.h>

/**
 * check_fd - Checks if the file descriptor given to open is valid,
 * exits if not
 * @fd: check file descriptor
 * @ev: Environment vector (to free if fd is invalid)
 * @filename: The name of file that attempted to be opened
 *
 * Return: void
 */
void check_fd(int fd, char **ev, char *filename)
{
	if (fd == -1)
	{
		char *m = _strcat(3, "./hsh: 0: Can't open ", filename, "\n");

		write(STDERR_FILENO, m, _strlen(m));
		free(m);
		free_arr(ev);
		exit(127);
	}
}

/**
 * read_file_content - reads files into a buffer
 * @filename: file name
 * @bytes_read: pointer to a variable to store total bytes
 * read
 * @ev: Environment variables vector
 *
 * Return: buffer containing file content
 */
char *read_file_content(char *filename, size_t *bytes_read, char **ev)
{
	int fd = open(filename, O_RDONLY);
	struct stat filestat;
	char *buffer;
	size_t total_bytes_read = 0;

	check_fd(fd, ev, filename);
	if (fstat(fd, &filestat) == -1)
	{
		close(fd);
		return (NULL);
	}
	buffer = malloc(filestat.st_size + 1);
	if (buffer == NULL)
	{
		close(fd);
		return (NULL);
	}
	while ((long int) total_bytes_read < filestat.st_size)
	{
		size_t new_read_bytes = read(fd, buffer + total_bytes_read,
				filestat.st_size - total_bytes_read);

		if ((int) new_read_bytes == -1)
		{
			free(buffer);
			close(fd);
			return (NULL);
		}
		total_bytes_read += new_read_bytes;
	}
	buffer[total_bytes_read] = '\0';
	close(fd);
	*bytes_read = total_bytes_read;
	return (buffer);
}

/**
 * parse_lines - parses buffer and returns array of lines
 * @buffer: buffer to parse
 * @line_count: variable to store line count
 *
 * Return: array of lines
 */
char **parse_lines(char *buffer, size_t *line_count)
{
	char **lines = _strtok(buffer, "\n\0");
	int i = 0;

	while (lines[i])
	{
		(*line_count)++;
		i++;
	}
	free(buffer);
	return (lines);
}
/**
 * execute_from_file - executes command from file line by line
 * @av: argument vector
 * @ev: env
 *
 * Return: execution statis
 */
int execute_from_file(char **av, char **ev)
{
	size_t bytes_read;
	size_t line_count = 0;
	char *buffer;
	char **lines;
	int i, status = 0;

	buffer = read_file_content(av[1], &bytes_read, ev);
	if (!buffer)
	{
		return (0);
	}
	lines = parse_lines(buffer, &line_count);
	for (i = 0; lines[i]; i++)
	{
		exec_command(av, lines[i], ev, 0, &status);
	}
	free(lines);
	return (0);
}

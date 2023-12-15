#include "main.h"

/**
 * print_error - prints errno msg to stderr
 * @shl_name: Current name of the executable (shell)
 * @cmd: the failed command
 * @msg: error message
 * @command_count: The current command number
 *
 * Return: void
 */
void print_error(char *shl_name, char *cmd, char *msg, int command_count)
{
	char *cc = num_to_str(command_count);
	char *err;

	err = _strcat(7, shl_name, ": ", cc, ": ", cmd, ": ", msg);
	write(STDERR_FILENO, err, _strlen(err));
	free(err);
	free(cc);
}
/**
 * get_path - gets full path of a command if it is not a path
 * itself
 * @command: input command string
 *
 * Return: command to excute
 */
char *get_path(char *command)
{
	char **paths = get_paths();
	char *c_path;

	if (!_strchr(command, '/'))
	{
		c_path = command_path(paths, command);
		if (c_path == NULL)
		{
			free_arr(paths);
			return (NULL);
		}
	}
	else
		c_path = command;
	free_arr(paths);
	return (c_path);
}

/**
 * check_file - Checks if there is a file of commands to execute from
 * @av: Argument vector
 * @ev: Environment Vector
 * @status: Pointer to the status of the program
 *
 * void
 */
void check_file(char **av, char **ev, int *status)
{
	if (av[1])
	{
		*status = execute_from_file(av, ev);
		free_arr(ev);
		exit(*status);
	}
}

/**
 * main - Displays prompt, accepts user command + arguments, parses, executes
 * @ac: Argument Count
 * @av: Argument Vector
 * @ev: Environment Vector
 *
 * Return: Always 0 (Success)
 */
int main(__attribute__((unused)) int ac, char **av,
	 char **ev)
{
	int command_count = 0, stat = 0;

	ev = init_env();
	while (1)
	{
		char *line_buffer = NULL;
		size_t buff_size = 0;
		int status = 0, line_size = 0;

		check_file(av, ev, &status);
		if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || ac != 1)
		{
			line_size = getline_multi(&line_buffer, &buff_size);
			++command_count;
			status = exec_command(av, line_buffer, environ,
					      command_count, &stat);
			break;
		}
		line_size = getline(&line_buffer, &buff_size, stdin);
		if (line_size <= 1)
		{
			if (line_size == -1)
			{
				write(STDOUT_FILENO, "\n", 1);
				free(line_buffer);
				break;
			}
			free(line_buffer);
			continue;
		}
		if ((int) line_size == -1)
			exit_program(&line_buffer, line_size, command_count, &stat);
		++command_count;
		status = exec_command(av, line_buffer, environ, command_count, &stat);
		if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || ac != 1)
			break;
	}
	free_arr(ev);
	return (stat);
}

/**
 * exec_command - excutes built-in and system commands
 * @av: array containing command and args
 * @line: Buffer containing the data read from stdin
 * @ev: environment
 * @cmd_cnt: The current command number
 * @status: The exit status of the last executed command
 *
 * Return: status - 0 -> success, 1-> command not found
 * 2 -> command excution failed
 */

int exec_command(char **av, char *line, char **ev, int cmd_cnt, int *status)
{
	/**int i = 0, j;**/
	char **uncommented, **commands, *hash;

	if (line[0] == '#')
	{
		free(line);
		return (0);
	}
	hash = _strchr(line, '#');
	if (hash != NULL && *(hash - 1) == ' ')
	{
		uncommented = _strtok(line, "#");
		free(line);
		commands = _strtok(uncommented[0], ";\n");
		free_arr(uncommented);
	}
	else
	{
		commands = _strtok(line, ";\n");
		free(line);
	}
	exec_line_commands(commands, av, ev, cmd_cnt, status);
	free_arr(commands);
	return (0);
}

#include "main.h"

/**
 * execute_fork - Create a child process to execute a command
 * @c_path: The command to execute
 * @args: The arguments along with the command to be executed
 * @av: 1d array of the command line arguments given when the program is run
 * @ev: Environment variables
 * @cmd_cnt: The current command number
 * @status: Pointer at the exit status of the last executed command
 * @commands: The commands given to be freed
 *
 * Return: void
 */
void execute_fork(char *c_path, char **args, char **av, char **ev, int cmd_cnt,
		  int *status, char **commands)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		*status = 2;
		exit(2);
	}
	if (child_pid == 0)
	{
		*status = execve(c_path, args, ev);
		if (*status == -1)
		{
			*status = 2;
			print_error(av[0], args[0], "execution failed\n",
				    cmd_cnt);
			free_arr(commands);
			free_arr(args);
			exit(2);
		}
	}
	else
	{
		wait(status);
	}
}


/**
 * exec_line_commands - Execute commands received from stdin
 * @commands: The commands to be executed
 * @av: Argument vector
 * @ev: Environment vector
 * @cmd_cnt: The current command number
 * @status: Pointer at the exit status of the last executed command
 *
 * Return: void
 */
void exec_line_commands(char **commands, char **av, char **ev, int cmd_cnt,
		    int *status)
{
	int i = 0;
	char *c_path;

	while (commands && commands[i])
	{
		char **args = _strtok(commands[i], " \t");

		args = replace_variables(args, *status);
		if (args[0] == NULL)
		{
			i++;
			free_arr(args);
			continue;
		}
		if (!_strcmp(args[0], "exit"))
		{
			free_arr(commands);
			exit_program(args, i, cmd_cnt, status);
		}
		if (_strchr(args[0], '/') == NULL)
		{
			if (is_builtin(args[0]) == 1)
			{
				execute_builtin(args, av, cmd_cnt);
				free_arr(args);
				i++;
				continue;
			}
			c_path = get_path(args[0]);
		}
		else
			c_path = args[0];
		if (is_path_null(c_path, status, &i, args, av, cmd_cnt))
			continue;
		execute_fork(c_path, args, av, ev, cmd_cnt, status, commands);
		free_if_malloced(c_path, args[0]);
		free_arr(args);
		i++;
	}
}

/**
 * is_path_null - Checks if extracted path of a command is NULL and performs
 * appropriate action if so
 * @c_path: The extracted command path
 * @status: Pointer to the status of the last executed command
 * @iter: Pointer to the iterator of the calling function
 * @args: Arguments given from the user
 * @av: Argument vector given to name which holds the name of the program
 * @cmd_cnt: The current command count/number
 *
 * Return: 1 if c_path is NULL, 0 otherwise
 */
int is_path_null(char *c_path, int *status, int *iter, char **args, char **av,
		 int cmd_cnt)
{
	if (c_path == NULL)
	{
		*status = 127;
		print_error(av[0], args[0], "not found\n", cmd_cnt);
		(*iter)++;
		free_arr(args);
		return (1);
	}
	return (0);
}

#include "main.h"

/**
 * is_builtin - checks if a command is a builtin
 * @cmd: command to be checked
 *
 * Return: 1 if cmd is builtin, 0 otherwise
 */
int is_builtin(char *cmd)
{
	int i = 0;
	char *commands[] = {"env", "cd", "setenv", "unsetenv"};

	while (i < 4)
	{
		if (_strcmp(cmd, commands[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

/**
 * execute_builtin - finds built-in handdle and excutes it
 * @args: Arguments given along with the command
 * @av: 1d array of the command line arguments given when the program is
 * executed
 * @cmd_no: The current command number
 *
 * Return: 0 on success
 */
int execute_builtin(char **args, char **av, int cmd_no)
{
	int i = 0;
	char *command = args[0];
	int (*func)(char **args, char **av, int cmd_no);
	built_in built_ins[] = {
		{"env", _env},
		{"cd", _cd},
		{"setenv", _setenv},
		{"unsetenv", _unsetenv}
	};

	while (i < 4)
	{
		if (_strcmp(command, built_ins[i].name) == 0)
		{
			func = built_ins[i].func;
			break;
		}
		i++;
	}
	if (!func)
		return (1);
	return ((*func)(args, av, cmd_no));
}

#include "main.h"

/**
 * _cd - it changes current working directory of the process for cd command
 * @args: Arguments
 * @av: An array of the command line arguments given when the program
 * was executed
 * @cmd_no: current command number
 *
 * Return: successful (0), -1 otherwise
 */
int _cd(char **args, char **av, int cmd_no)
{
	char *buff = malloc(1024), *old_buff = "";
	char *pwd = NULL, *old_pwd, *home, *dir;

	pwd = &get_env_var("PWD")[4];
	old_pwd = &get_env_var("OLDPWD")[7];
	home = &get_env_var("HOME")[5];
	old_buff = _strcat(2, old_buff, pwd);
	dir = args[1];
	if (args[1] == NULL)
		dir = home;
	else if (!_strcmp(args[1], "-"))
	{
		dir = old_pwd;
	}
	if (chdir(dir) == 0)
	{
		buff = getcwd(buff, 1024);
		set_env_var("PWD", buff);
		set_env_var("OLDPWD", old_buff);
		if (args[1] != NULL && !_strcmp(args[1], "-"))
		{
			write(STDOUT_FILENO, buff, _strlen(buff));
			write(STDOUT_FILENO, "\n", 1);
		}
	}
	else
	{
		char *msg = _strcat(3, "can't cd to ", args[1], "\n");

		print_error(av[0], args[0], msg, cmd_no);
		free(msg);
		return (-1);
	}
	free(buff);
	free(old_buff);
	return (0);
}

/**
 * _env - environment variables of the process are printed
 * @args: Arguments 
 * @av: array of the command line arguments given when the program is
 * executed
 * @cmd_no: current command number
 *
 * Return: successful (0) , -1 otherwise
 */
int _env(char **args, char **av, int cmd_no)
{
	char **ptr, *str;

	if (args[1] != NULL)
	{
		print_error(av[0], args[0], "Usage: env", cmd_no);
		return (-1);
	}
	ptr = environ;
	while (ptr != NULL && *ptr != NULL)
	{
		str = _strcat(2, *ptr, "\n");
		write(STDOUT_FILENO, str, _strlen(str));
		free(str);
		ptr++;
	}
	return (0);
}

/**
 * _setenv - modify an existing environment variable or create a new one
 * @args: Arguments
 * @av: array of the command line arguments given when the program is
 * executed
 * @cmd_no: current command number
 *
 * Return: successful (0), -1 otherwise
 */
int _setenv(char **args, char **av, int cmd_no)
{
	if (args[1] == NULL || args[2] == NULL)
	{
		print_error(av[0], args[0], "Usage: setenv VARIABLE VALUE\n",
			    cmd_no);
		return (-1);
	}
	if (set_env_var(args[1], args[2]) == -1)
	{
		char *msg = _strcat(3, "can't set the variable ", args[1], "\n");

		print_error(av[0], args[0], msg, cmd_no);
		free(msg);
		return (-1);
	}
	return (0);
}

/**
 * _unsetenv - environment variable is removec
 * @args: Arguments 
 * @av: array of the command line arguments given when the program is
 * executed
 * @cmd_no: current command number
 *
 * Return: successful (0), -1 otherwise
 */
int _unsetenv(char **args, char **av, int cmd_no)
{
	int m = 0;

	if (args[1] == NULL)
	{
		print_error(av[0], args[0], "Usage: unsetenv VARIABLE\n", cmd_no);
		return (-1);
	}
	while (environ[m])
	{
		char **str_arr = _strtok(environ[m], "=");

		if (!_strcmp(str_arr[0], args[1]))
		{
			free_arr(str_arr);
			break;
		}
		m++;
		free_arr(str_arr);
	}
	if (environ[m] == NULL)
	{
		char *msg = _strcat(3, "can't unset the variable ", args[1],
				    "\n");

		print_error(av[0], args[0], msg, cmd_no);
		free(msg);
		return (-1);
	}
	free(environ[m]);
	while (environ[m] != NULL)
	{
		environ[m] = environ[m + 1];
		m++;
	}
	return (0);
}

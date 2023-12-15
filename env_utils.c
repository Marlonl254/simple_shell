#include "main.h"

/**
 * get_paths - list of env paths returned
 *
 * Return: paths lists
 */
char **get_paths(void)
{
	int m;
	char *path;
	char **paths;

	for (m = 0; environ && environ[m]; m++)
	{
		char **key = _strtok(environ[m], "=");

		if (_strcmp(key[0], "PATH") == 0)
		{
			path = key[1];
			if (path == NULL || path[0] == '\0' ||
			    !_strcmp(path, "''"))
			{
				free_arr(key);
				return (NULL);
			}
			paths = _strtok(path, ":");
			free_arr(key);
			return (paths);
		}
		else
			free_arr(key);
	}
	return (NULL);
}

/**
 * command_path - full path of command is founded
 * @dirs: directories to search into
 * @command: command name
 *
 * Return: full path of command if found,
 * NULL if not
 */
char *command_path(char **dirs, char *command)
{
	int m;
	char *path = NULL;

	for (m = 0; dirs && dirs[m]; m++)
	{
		DIR *dir = opendir(dirs[m]);
		struct dirent *file;

		while ((file = readdir(dir)) != NULL)
		{
			if (_strcmp(command, file->d_name) == 0)
			{
				path = dirs[m];
				break;
			}
		}
		closedir(dir);
		if (path != NULL)
		{
			path = _strcat(3, path, "/", command);
			return (path);
		}
	}
	return (NULL);
}

/**
 * get_env_var - Retrieves variable - value pair from environ
 * @var_name: Variable name of the pair to retrieve
 *
 * Return: A pair with the given var_name if it exists, NULL if it doesn't
 */
char *get_env_var(char *var_name)
{
	char *env_var = NULL;
	int m = 0;

	while (environ && environ[m])
	{
		char **str_arr = _strtok(environ[m], "=");

		if (!_strcmp(str_arr[0], var_name))
			env_var = environ[m];
		m++;
		free_arr(str_arr);
	}
	return (env_var);
}

/**
 * set_env_var - value of a given var from environ is set
 * @var: variable name
 * @val: variable set
 *
 * Return: successful (0), 1 otherwise
 */
int set_env_var(char *var, char *val)
{
	int m = 0;
	char *ptr;

	while (environ[m])
	{
		char **str_arr = _strtok(environ[m], "=");

		if (!_strcmp(var, str_arr[0]))
		{
			free_arr(str_arr);
			break;
		}
		m++;
		free_arr(str_arr);
	}
	if (environ[m] == NULL)
	{
		extend_environ();
		environ[m + 1] = NULL;
	}
	ptr = environ[m];
	free(ptr);
	environ[m] = _strcat(3, var, "=", val);
	if (environ[m] == NULL)
		return (-1);
	return (0);
}

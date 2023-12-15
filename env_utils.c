#include "main.h"

/**
 * get_paths - returns list of env paths
 *
 * Return: list of paths
 */
char **get_paths(void)
{
	int i;
	char *path;
	char **paths;

	for (i = 0; environ && environ[i]; i++)
	{
		char **key = _strtok(environ[i], "=");

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
 * command_path - finds full path of a command
 * @dirs: directories to shearch in
 * @command: command name
 *
 * Return: full path of command if found,
 * NULL if not
 */
char *command_path(char **dirs, char *command)
{
	int i;
	char *path = NULL;

	for (i = 0; dirs && dirs[i]; i++)
	{
		DIR *dir = opendir(dirs[i]);
		struct dirent *file;

		while ((file = readdir(dir)) != NULL)
		{
			if (_strcmp(command, file->d_name) == 0)
			{
				path = dirs[i];
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
 * get_env_var - Retrieve a variable - value pair from environ
 * @var_name: Variable name of the pair to retrieve
 *
 * Return: A pair with the given var_name if it exists, NULL if it doesn't
 */
char *get_env_var(char *var_name)
{
	char *env_var = NULL;
	int i = 0;

	while (environ && environ[i])
	{
		char **str_arr = _strtok(environ[i], "=");

		if (!_strcmp(str_arr[0], var_name))
			env_var = environ[i];
		i++;
		free_arr(str_arr);
	}
	return (env_var);
}

/**
 * set_env_var - Sets the value of a given var from environ
 * @var: The name of the variable
 * @val: The value to set to the variable
 *
 * Return: 0 if successful, 1 otherwise
 */
int set_env_var(char *var, char *val)
{
	int i = 0;
	char *ptr;

	while (environ[i])
	{
		char **str_arr = _strtok(environ[i], "=");

		if (!_strcmp(var, str_arr[0]))
		{
			free_arr(str_arr);
			break;
		}
		i++;
		free_arr(str_arr);
	}
	if (environ[i] == NULL)
	{
		extend_environ();
		environ[i + 1] = NULL;
	}
	ptr = environ[i];
	free(ptr);
	environ[i] = _strcat(3, var, "=", val);
	if (environ[i] == NULL)
		return (-1);
	return (0);
}

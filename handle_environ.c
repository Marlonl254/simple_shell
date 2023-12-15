#include "main.h"

/**
 * init_env - Re-creates environ using dynamic memory allocation for freeing
 *
 * Return: environ
 */
char **init_env(void)
{
	size_t i = 0, j;
	char **new_environ;

	while (environ && environ[i])
		i++;
	new_environ = malloc(sizeof(char *) * (i + 1));
	if (new_environ != NULL)
	{
		i = 0;
		while (new_environ && environ && environ[i])
		{
			new_environ[i] = malloc(sizeof(char) *
						(_strlen(environ[i]) + 1));
			for (j = 0; new_environ[i] && j <= _strlen(environ[i]);
			     j++)
				new_environ[i][j] = environ[i][j];
			i++;
		}
		new_environ[i] = NULL;
		environ = new_environ;
	}
	return (new_environ);
}

/**
 * extend_environ - Extends the environ array for a env variable
 *
 * Return: void
 */
void extend_environ(void)
{
	size_t i = 0, j;
	char **new_environ;

	while (environ && environ[i])
		i++;
	new_environ = malloc(sizeof(char *) * (i + 2));
	if (new_environ != NULL)
	{
		i = 0;
		while (new_environ && environ && environ[i])
		{
			new_environ[i] = malloc(sizeof(char) *
						(_strlen(environ[i]) + 1));
			for (j = 0; new_environ[i] && j <= _strlen(environ[i]);
			     j++)
				new_environ[i][j] = environ[i][j];
			i++;
		}
		new_environ[i] = NULL;
		free_arr(environ);
		environ = new_environ;
	}
}

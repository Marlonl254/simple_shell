#include "main.h"

/**
 * is_interactive - Checks if the shell is in interactive mode or not
 *
 * Return: 1 if it is interactive, 0 otherwise
 */
int is_interactive(void)
{
	char *shlvl = "";
	int i = 0;

	while (environ && environ[i])
	{
		char **str_arr = _strtok(environ[i], "=");

		if (!_strcmp(str_arr[0], "SHLVL"))
			shlvl = &environ[i][6];
		free_arr(str_arr);
		i++;
	}
	if (!_strcmp(shlvl, "1"))
		return (1);
	return (0);
}

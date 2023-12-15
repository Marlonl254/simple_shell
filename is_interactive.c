#include "main.h"

/**
 * is_interactive - Checks if the shell is in interactive mode or not
 *
 * Return: interactive (1), 0 otherwise
 */
int is_interactive(void)
{
	char *shlvl = "";
	int m = 0;

	while (environ && environ[m])
	{
		char **str_arr = _strtok(environ[m], "=");

		if (!_strcmp(str_arr[0], "SHLVL"))
			shlvl = &environ[m][6];
		free_arr(str_arr);
		m++;
	}
	if (!_strcmp(shlvl, "1"))
		return (1);
	return (0);
}

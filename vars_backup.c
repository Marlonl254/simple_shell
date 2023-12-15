#include "main.h"

/**
 * replace_variables - Replace variables given as arguments/commands
 * @args: arguments
 * @status: Exit status of last executed command
 *
 * Return: void
 */
char **replace_variables(char **args, int status)
{
	int i = 0;

	while (args[i] != NULL)
	{
		if (args[i][0] == '$')
		{
			if (!_strcmp(args[i], "$$"))
			{
				pid_t process_id = getpid();

				free(args[i]);
				args[i] = _strcat(1, num_to_str(process_id));
			}
			else if (!_strcmp(args[i], "$?"))
			{
				free(args[i]);
				args[i] = _strcat(1, num_to_str(status));
			}
			else
			{
				char *env_var = get_env_var(&args[i][1]);
				size_t len = _strlen(args[i]);

				if (env_var != NULL)
				{
					free(args[i]);
					args[i] = _strcat(1,
							  &env_var[len]);
				}
			}
		}
		i++;
	}
	return (args);
}

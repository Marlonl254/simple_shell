#include "main.h"

/**
 * exit_program - Exits running shell
 * @buff_arr: array of command and arguments
 * @buff_size: Number of characters in buff_arr
 * @cmd_cnt: command number
 * @stat: Pointer to the exit status of the last executed command
 *
 * Return: void
 */
void exit_program(char **buff_arr, size_t buff_size, int cmd_cnt, int *stat)
{
	free_arr(environ);
	if ((int) buff_size == -1)
	{
		free_arr(buff_arr);
		write(STDOUT_FILENO, "\n", 1);
		exit(0);
	}
	if (buff_arr[1] != NULL)
	{
		int status = 0;
		char *ptr = buff_arr[1];

		while (*ptr)
		{
			if (*ptr < 48 || *ptr > 57)
			{
				char *cc = num_to_str(cmd_cnt);
				char *msg = _strcat(6, "./hsh: ", cc,
						    ": exit: Illegal number",
						    ": ", buff_arr[1], "\n");
				write(2, msg, _strlen(msg));
				free(cc);
				free(msg);
				free_arr(buff_arr);
				exit(2);
			}
			status = (status * 10) + (*ptr - 48);
			ptr++;
		}
		free_arr(buff_arr);
		exit(status);
	}
	free_arr(buff_arr);
	if (*stat != 0)
		exit(2);
	exit(0);
}

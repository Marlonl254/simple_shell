#ifndef MAIN_H
#define MAIN_H

/** Header files **/
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <stdarg.h>
#include <errno.h>

/** Global vars **/
extern char **environ;

/** Utility functions **/
char *_strchr(char *, char);
int _strcmp(char *, char *);
size_t _strlen(char *);
char **_strtok(char *, char *);
char *_strcat(int, ...);
char *_strcpy(char *, char *);
char *_memcpy(char *, char *, unsigned int);
char *num_to_str(unsigned int);
void *_realloc(void *, unsigned int, unsigned int);
void free_arr(char **);
void free_strs(int, ...);
void free_if_malloced(char *, char *);
char **get_paths(void);
char *command_path(char **, char *);
char *get_path(char *);
int getline_multi(char **, size_t *);
void print_prompt(void);
void print_error(char *, char *, char *, int);
void exit_program(char **, size_t, int, int *);
int is_interactive(void);
char *get_env_var(char *);
int set_env_var(char *, char *);
char **replace_variables(char **, int);
char **init_env(void);
void extend_environ(void);
int is_path_null(char *, int *, int *, char **, char **, int);

/** command  execution **/
void exec_line_commands(char **, char **, char **, int, int *);
int exec_command(char **, char *, char **, int, int *);
void execute_fork(char *, char **, char **, char **, int, int *, char **);
int execute_from_file(char **, char **);

/** built-in functions **/
int is_builtin(char *);
int execute_builtin(char **, char **, int);
int _cd(char **, char **, int);
int _env(char **, char **, int);
int _setenv(char **, char **, int);
int _unsetenv(char **, char **, int);

/** structs **/

/**
 * struct built_in - A struct for assigning a function to special commands
 * @name: The name of the command
 * @func: The function to handle the command
 */
typedef struct built_in
{
	char *name;
	int (*func)(char **, char **, int);
} built_in;

#endif

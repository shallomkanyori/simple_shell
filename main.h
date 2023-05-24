#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define BUFF_SIZE 1024
#define BUFF_FLUSH -1
#define INT_STR_SIZE 20

/**
 * struct shdata - A shell data struct
 * struct bi - A struct for the builtin functions
 * @av: the program arguments
 * @env: the environment variables
 * @cmd: the array containing the current command and its arguments
 * @input: the user input string
 * @path: the value of the PATH environment variable
 * @interactive: holds whether or not the shell is in interactive mode
 * @line_num: the number of lines processed so far
 * @line_num_str: holds the string conversion of line_num
 * @res: the return value of main
 * @err_message: holds custom shell error messages
 * @err_incl_cmd: whether to include the command name in the custon error
 * message
 *
 * Description: A struct that holds the relevant data of the shell
 */
typedef struct shdata
{
	char **av;
	char **env;
	char **cmd;
	char *input;
	char *path;
	int interactive;
	unsigned int line_num;
	char line_num_str[INT_STR_SIZE];
	int res;

	char *err_message;
	int err_incl_cmd;
} shdata_t;
/**
 * struct bi - A struct for the builtin functions
 * @name: the name of the command
 * @func: the actual builtin function
 *
 * Description: A struct that maps a command name to a builtin function
 */
typedef struct bi
{
	char *name;
	int (*func)(shdata_t *sh_data);
} bi_t;
/*exec functions*/
int check_builtin(char *cmd, bi_t builtins[]);

/*string functions*/
int _strcmp(char *s1, char *s2);
void free_shdata(shdata_t *sh_data);

/*builtins*/
int _myexit(shdata_t *sh_data);

/*write helpers */
int putchr(char c);
int putstr(char *str);

/* error handling functions */
void print_error(shdata_t *sh_data);
int put_str_err(char *str);
int put_chr_err(char c);

/* exec functions */
int handle_cmd(shdata_t *sh_data);
int exec_cmd(shdata_t *sh_data, char *cmd_path);
char *get_path(char **env);
void search_path(shdata_t *sh_data, char **full_path, int *found);

/* string functions */
char *_strdup(char *str);
int _strlen(char *str);
int _strncmp(char *s1, char *s2, int n);
char *_strcpy(char *dest, char *src);
char *_strcat(char *dest, char *src);
char *_strchr(char *str, char c);
void *_memcpy(void *dest, void *src, unsigned int n);

/* memory functions */
void *_realloc(void *ptr, unsigned int s_old, unsigned int s_new);
void free_ptr(void **ptr);

/* util functions */
char *itoa(unsigned int n, char *res);

#endif /* MAIN_H */

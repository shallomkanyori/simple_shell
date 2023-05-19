#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void print_error(char **av, int *res);

/* exec functions */
int handle_cmd(char **cmd, char **av, char **env, int *res);
int exec_cmd(char **cmd, char **av, char **env, int *res);
char *get_path(char **env);
void search_path(char *path, char **full_path, char **cmd, char **av,
		int *res);

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

#endif /* MAIN_H */

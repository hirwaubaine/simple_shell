#ifndef SHELL_H
#define SHELL_H
#define MAX_COMMANDS 20

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <errno.h>

#define END_OF_FILE -2
#define EXIT -3

extern char **environ;

char *name;

int hist;

/**
 * struct list_s - A new struct type defining a linked list
 * @dir: A directory path
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin commands
 * @name: The name of the builtin command
 * @func: A function pointer to the builtin command's function
 */

typedef struct builtin_s
{
	char *name;
	int (*func)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another structure
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

alias_t *aliases;

ssize_t _getline(char **lineptr, size_t *n, FILE *strm);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *dlm);
char *location(char *command);
list_t *path_dir(char *path);
int execute(char **args, char **front);
void free_list(list_t *head);
char *_itoa(int num);

void handle_line(char **line, ssize_t read);
void var_rep(char **args, int *exec_ret);
char *get_args(char *line, int *exec_ret);
int call_args(char **args, char **front, int *exec_ret);
int run_args(char **args, char **front, int *exec_ret);
int handle_args(int *exec_ret);
int check_args(char **args);
void free_args(char **args, char **front);
char **rep_aliases(char **args);

int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

int (*get_builtin(char *command))(char **args, char **front);
char **_copyenviron(void);
void free_environ(void);
char **_getenviron(const char *var);

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

int create_error(char **args, int err);
char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
char *error_126(char **args);
char *error_127(char **args);

alias_t *add_alias_end(alias_t **head, char *name, char *value);
void free_alias_list(alias_t *head);
list_t *add_node_end(list_t **head, char *dir);
void free_list(list_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int proc_file_commands(char *file_path, int *exe_ret);
#endif

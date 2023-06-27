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

/**
 * prompt - Promtpt of the shell
 * @agv: variable arguments
 * @environ: environment variables
 */
typedef struct builtin_s
{
	char *command;
	size_t(*fptr)(char **);
}builtin_t;

char *path(char *);
void exec_command(char **, char **, char **);
ssize_t _getline(char **, size_t *, FILE *);
int pathchk(char *);
char **split_line(char *);
int _strlen(char *);
int _atoi(char *);
int _strcmp(char *, char *);
char *_strcat(char *, char *);
size_t setenviron(char **);
size_t my_exit(char **);
size_t _setenviron(char **);
size_t builtinm(char **);
int main(int argc, char *argv[], char *environ[]);
void prompt(char **agv, char **environ);

#endif

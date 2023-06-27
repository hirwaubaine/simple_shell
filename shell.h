#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

/**
 * prompt - Promtpt of the shell
 * @agv: variable arguments
 * @environ: environment variables
 */
int main(int argc, char *argv[], char *environ[]);
void prompt(char **agv, char **environ);

#endif

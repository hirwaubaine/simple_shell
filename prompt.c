#include "shell.h"
#define MAX_COMMAND 100

/**
 * prompt - Prompt for the shell built
 * @agv: array of argument
 * @environ: environment variables
 * Rerurn: always 0
 */

void prompt(char **agv, char **environ)
{
	char *strg = NULL;
	int i, status, j;
	size_t n = 0;
	ssize_t n_char;
	char *argv[MAX_COMMAND];
	pid_t child_pid;

	while (1)
	{
		printf("cisfun$ ");

		n_char = getline(&strg, &n, stdin);
		if (n_char == -1)
		{
			free(strg);
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (strg[i])
		{
			if (strg[i] == '\n')
				strg[i] = 0;
			i++;
		}
		j = 0;
		argv[j] = strtok(strg, " ");
		while (strg[j])
		{
			j++;
			argv[j] = strtok(NULL, " ");
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			free(strg);
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			if (execve(argv[0], argv, environ) == -1)
				printf("%s: No such file or directory\n", agv[0]);
		}
		wait(&status);
	}
}

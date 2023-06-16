#include "shell.h"

void prompt(char **agv, char **environ)
{
	char *strg = NULL;
	int i, status;
	ssize_t n_char;
	size_t n = 0;
	char *argv[] = {NULL, NULL};
	pid_t child_pid;

	while (1)
	{
		printf("simple_shell$ ");

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
		}
		argv[0] = strg;
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

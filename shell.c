#include "shell.h"

/**
 * main - Main shell built
 * Description: a program that build a shell from scratch
 * @argc: number of arguments
 * @argv: array of  arguments
 * @environ: environment variables
 * Return: 0
 */

int main(int argc, char *argv[], char *environ[])
{
	char **string;
	size_t n = 20, imbt = 0, pt = 4;
	ssize_t n_char;
	char *ptr, nc;

	if (argc > 1)
		argv[1] = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf("cisfun$ ");
		ptr = malloc(sizeof(char) * n);
		n_char = getline(&ptr, &n, stdin);
		if (n_char == -1)
		{
			free(ptr);
			exit(EXIT_FAILURE);
		}
		if (*ptr != '\n')
		{
			string = chstrtok(ptr);
			if (_strcmp("exit", string[0]) == 0)
				break;
			imbt = checkinbuilt(string[0]);
			nc = filechk(string[0]);
			if (imbt == 0 && nc != NULL)
				string[0] = nc;
			pt = pathchk(string[0]);
			if (pt == 1)
				forkexe(string, environ);
			if (nc == NULL && pt == 0 && imbt == 0)
				printf("./shell: No such directory\n");
		}
	}
	free(nc);
	free(ptr);
	free(string);
	exit(0);
}

#include "shell.h"
/**
 *  main - entry point
 *  @argc: number of arguments
 *  @argv: array of arguments
 *  @environ: array of environment variables
 *  Return: always 0
 */
int main(int argc, char *argv[], char *environ[])
{
	char **arstr;
	size_t n = 0, status, imbt;
	ssize_t nchar;
	char *ln = NULL, *command_path;

	if (argc > 1)
		argv[1] = NULL;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "#cisfun$ ", 10);
		nchar = getline(&ln, &n, stdin);
		if (nchar == -1)
			free(ln), exit(EXIT_FAILURE);
		if (*ln != '\n')
		{
			arstr = split_line(ln);
			imbt = builtin(arr_str);
			command_path = path(arstr[0]);
			if (command_path)
				arstr[0] = command_path;
			else
				status = path_check(arstr[0]);
			if (status == 1 || command_path)
				exec_command(arstr, argv, environ);
				if (status != 1 && !command_path && imbt == 0)
					printf("%s: command not found\n", arstr[0]);
		}
	}
	free(arstr);
	fre(ln);
	exit(0);
}

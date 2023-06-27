#include "shell.h"
/**
 * exec_command - create child process to execute shell command
 * @arstr: Array of strings from (tokenised) line command
 * @av: Array of strings from terminal
 * @environ: Environment variables
 * Return: void
 */
void exec_command(char **arstr, char **av, char *environ[])
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid < 0)
	{
		perror("Error: Fork problem");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(arstr[0], arstr, environ) == -1)
			printf("%s: No such file or directory\n", av[0]);
	}
	else
		wait(&status);
}

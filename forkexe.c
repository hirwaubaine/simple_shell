#include <stdio.h>
#include <sys/wait.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * forkexe - fork execution system
 * @arstr: array of strings
 * @environ: environment variable
 * Return: void
 */
void forkexe(char **arstr, char *environ[])
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
			perror("./shell: No such file or directory\n");
		else
		{
			waitpid(child_pid, &status, 0);
		}
	}

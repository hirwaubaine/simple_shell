#include "shell.h"

/**
 * main - Main shell built
 * Description: a program that build a shell from scratch
 * @agc: number of arguments
 * @agv: array of  arguments
 * @environ: environment variables
 * Return: 0
 */

int main(int agc, char **agv, char **environ)
{
	if (agc == 1)
		prompt(agv, environ);
	return (0);
}

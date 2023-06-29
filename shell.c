#include "shell.h"

void sgl_handler(int sgl);
int execute(char **args, char **front);
/**
 * sgl_handler - Prints a new prompt upon a signal
 * @sgl: signal
 */
void sgl_handler(int sgl)
{
	char *new_prompt = "\n#cisfun$ ";

	(void)sgl;
	signal(SIGINT, sgl_handler);
	write(STDIN_FILENO, new_prompt, 10);
}
/**
 * execute - Executes a command in a child process
 * @args: An array of arguments
 * @front: A double pointer to the beginning of args
 * Return: If an error occurs - an error code
 * O/w - The exit value of the last executed command
 */
int execute(char **args, char **front)
{
	pid_t child_pid;
	int status, flag = 0, rtn = 0;
	char *command = args[0];

	if (command[0] != '/' && command[0] != '.')
	{
		flag = 1;
		command = location(command);
	}
	if (!command || (access(command, F_OK) == -1))
	{
		if (errno == EACCES)
			rtn = (create_error(args, 126));
		else
			rtn = (create_error(args, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(command);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(command, args, environ);
			if (errno == EACCES)
				rtn = (create_error(args, 126));
			free_environ();
			free_args(args, front);
			free_alias_list(aliases);
			_exit(rtn);
		}
		else
		{
			wait(&status);
			rtn = WEXITSTATUS(status);
		}
	}
		if (flag)
			free(command);
		return (rtn);
}
/**
 * main - Runs a simple UNIX command interpreter
 * @argc: The number of arguments supplied to the program
 * @argv: An array of pointers to the arguments
 * Return: The return value of the last executed command
 */

int main(int argc, char *argv[])
{
	int rtn = 0, retn;
	int *exec_ret = &retn;
	char *prompt = "#cisfun$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, sgl_handler);

	*exec_ret = 0;
	environ = _copyenviron();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		rtn = proc_file_commands(argv[1], exec_ret);
		free_environ();
		free_alias_list(aliases);
		return (*exec_ret);
	}
	if (!isatty(STDIN_FILENO))
	{
		while (rtn != END_OF_FILE && rtn != EXIT)
			rtn = handle_args(exec_ret);
		free_environ();
		free_alias_list(aliases);
		return (*exec_ret);
	}
	while (1)
	{
		write(STDOUT_FILENO, prompt, 10);
		rtn = handle_args(exec_ret);
		if (rtn == END_OF_FILE || rtn == EXIT)
		{
			if (rtn == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 10);
			free_environ();
			free_alias_list(aliases);
			exit(*exec_ret);
		}
	}
	free_environ();
	free_alias_list(aliases);
	return (*exec_ret);
}

#include "shell.h"

char *get_args(char *line, int *exec_ret);
int call_args(char **args, char **front, int *exec_ret);
int run_args(char **args, char **front, int *exec_ret);
int handle_args(int *exec_ret);
int check_args(char **args);

/**
 * get_args - Gets a command from standard input
 * @line: A buffer to store the command
 * @exec_ret: The return value of the last executed command
 * Return: If an error occurs - NULL
 */
char *get_args(char *line, int *exec_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);
	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_args(line, exec_ret));
	}

	line[read - 1] = '\0';
	var_rep(&line, exec_ret);
	handle_line(&line, read);

	return (line);
}
/**
 * call_args - Partitions operators from commands and calls them
 * @args: An array of arguments
 * @front: A double pointer to the beginning of args
 * @exec_ret: return value of the parent process' last executed command
 * Return: The return value of the last executed command
 */
int call_args(char **args, char **front, int *exec_ret)
{
	int rtn, index;

	if (!args[0])
		return (*exec_ret);
	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], "||", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = rep_aliases(args);
			rtn = run_args(args, front, exec_ret);
			if (*exec_ret != 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (rtn);
			}
		}
		else if (_strncmp(args[index], "&&", 2) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			args = rep_aliases(args);
			rtn = run_args(args, front, exec_ret);
			if (*exec_ret == 0)
			{
				args = &args[++index];
				index = 0;
			}
			else
			{
				for (index++; args[index]; index++)
					free(args[index]);
				return (rtn);
			}
		}
	}
	args = rep_aliases(args);
	rtn = run_args(args, front, exec_ret);
	return (rtn);
}

/**
 * run_args - Calls the execution of a command.
 * @args: An array of arguments.
 * @front: A double pointer to the beginning of args.
 * @exec_ret: The return value of the last executed command
 * Return: The return value of the last executed command
 */
int run_args(char **args, char **front, int *exec_ret)
{
	int rtn, i;
	int (*builtin)(char **args, char **front);

	builtin = get_builtin(args[0]);

	if (builtin)
	{
		rtn = builtin(args + 1, front);
		if (rtn != EXIT)
			*exec_ret = rtn;
	}
	else
	{
		*exec_ret = execute(args, front);
		rtn = *exec_ret;
	}
	hist++;

	for (i = 0; args[i]; i++)
		free(args[i]);

	return (rtn);
}

/**
 * handle_args - Gets, calls, and runs the execution of a command.
 * @exec_ret: The return value of the last executed command
 * Return: If an end-of-file is read - END_OF_FILE (-2)
 * If the input cannot be tokenized - -1.  O/w - The exit value
 */
int handle_args(int *exec_ret)
{
	int rtn = 0, index;
	char **args, *line = NULL, **front;

	line = get_args(line, exec_ret);
	if (!line)
		return (END_OF_FILE);

	args = _strtok(line, " ");
	free(line);
	if (!args)
		return (rtn);
	if (check_args(args) != 0)
	{
		*exec_ret = 2;
		free_args(args, args);
		return (*exec_ret);
	}
	front = args;

	for (index = 0; args[index]; index++)
	{
		if (_strncmp(args[index], ";", 1) == 0)
		{
			free(args[index]);
			args[index] = NULL;
			rtn = call_args(args, front, exec_ret);
			args = &args[++index];
			index = 0;
		}
	}
	if (args)
		rtn = call_args(args, front, exec_ret);

	free(front);
	return (rtn);
}

/**
 * check_args - Checks if there are any leading ';', ';;', '&&', or '||'
 * @args: pointer to tokenized commands and arguments
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2
 * Otherwise - 0
 */
int check_args(char **args)
{
	size_t i;
	char *cur, *nxt;

	for (i = 0; args[i]; i++)
	{
		cur = args[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&args[i], 2));
			nxt = args[i + 1];
			if (nxt && (nxt[0] == ';' || nxt[0] == '&' || nxt[0] == '|'))
				return (create_error(&args[i + 1], 2));
		}
	}
	return (0);
}

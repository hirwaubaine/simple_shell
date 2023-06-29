#include "shell.h"

void free_args(char **args, char **front);
char *get_pid(void);
char *get_env_value(char *beginning, int len);
void var_rep(char **args, int *exec_ret);

/**
 * free_args - Frees up memory taken by args.
 * @args: A null-terminated double pointer containing commands/arguments.
 * @front: A double pointer to the beginning of args.
 */
void free_args(char **args, char **front)
{
	size_t i;

	for (i = 0; args[i] || args[i + 1]; i++)
		free(args[i]);

	free(front);
}
/**
 * get_pid - Gets the current process ID
 * Return: The current process ID or NULL on failure
 */
char *get_pid(void)
{
	size_t i = 0;
	char *buffer;
	ssize_t file;

	file = open("/proc/self/stat", O_RDONLY);
	if (file == -1)
	{
		perror("Cant read file");
		return (NULL);
	}
	buffer = malloc(120);
	if (!buffer)
	{
		close(file);
		return (NULL);
	}
	read(file, buffer, 120);
	while (buffer[i] != ' ')
		i++;
	buffer[i] = '\0';

	close(file);
	return (buffer);
}

/**
 * get_env_value - Gets the value corresponding to an environmental variable
 * @beginning: The environmental variable to search
 * @len: The length of the environmental variable to search
 * Return: If the variable is not found - an empty string
 */

char *get_env_value(char *beginning, int len)
{
	char **var_addr;
	char *replc = NULL, *tmp, *var;

	var = malloc(len + 1);
	if (!var)
		return (NULL);
	var[0] = '\0';
	_strncat(var, beginning, len);

	var_addr = _getenviron(var);
	free(var);
	if (var_addr)
	{
		tmp = *var_addr;
		while (*tmp != '=')
			tmp++;
		replc = malloc(_strlen(tmp) + 1);
		if (replc)
			_strcpy(replc, tmp);
	}
	return (replc);
}

/**
 * var_rep - Handles variable replacement
 * @line: A double pointer containing the command and arguments
 * @exec_ret: A pointer to the return value of the last executed command
 */
void var_rep(char **line, int *exec_ret)
{
	int j, k = 0, len;
	char *replc  = NULL, *old_line = NULL, *new_line;

	old_line = *line;
	for (j = 0; old_line[j]; j++)
	{
		if (old_line[j] == '$' && old_line[j + 1] &&
		    old_line[j + 1] != ' ')
		{
			if (old_line[j + 1] == '$')
			{
				replc = get_pid();
				k = j + 2;
			}
			else if (old_line[j + 1] == '?')
			{
				replc = _itoa(*exec_ret);
				k = j + 2;
			}
			else if (old_line[j + 1])
			{
				for (k = j + 1; old_line[k] &&
					     old_line[k] != '$' &&
					     old_line[k] != ' '; k++)
					;
				len = k - (j + 1);
				replc = get_env_value(&old_line[j + 1], len);
			}
			new_line = malloc(j + _strlen(replc)
					+ _strlen(&old_line[k]) + 1);
			if (!line)
				return;
			new_line[0] = '\0';
			_strncat(new_line, old_line, j);
			if (replc)
			{
				_strcat(new_line, replc);
				free(replc);
				replc = NULL;
			}
			_strcat(new_line, &old_line[k]);
			free(old_line);
			*line = new_line;
			old_line = new_line;
			j = -1;
		}
	}
}

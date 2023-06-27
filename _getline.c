#include "shell.h"
/**
 * _getline - Print "$ "
 * @line: buffer of string
 * @n: length of string
 * @stream: receive file
 * Return: length of input string
 */
ssize_t _getline(char **line, size_t *n, FILE *stream)
{
	char str[120];

	if (line == NULL || n == NULL || stream == NULL)
	{
		perror("Error! pointer proplem");
		exit(1);
	}
	if (*line == NULL)
	{
		*line = malloc(sizeof(str));
		if (*line == NULL)
		{
			perror("Unable to allocate memory");
			exit(1);
		}
	}
	*line[0] = '\0';
	while (fgets(*line, *n, stream))
	{
		if ((*n - strlen(*line)) < sizeof(str))
		{
			*n *= 2;
			*line = realloc(*line, *n);
			if (*line == NULL)
			{
				perror("Unable to reallocate memory");
				exit(1);
			}
		}
		strcat(*line, str);
		if ((*lineptr)[strlen(*line) - 1] == '\n')
			return (strlen(*line));
	}
	return (0);
}

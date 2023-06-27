#include <stdio.h>
#include <stdlib.h>
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
/**
 * chstrtok - Print "$ "
 * @str: string parameter
 * Return: array of string
 */

char **chstrtok(char *str)
{
	char **arst, *pars;
	int i = 0, j = 0;

	arst = malloc(8 * sizeof(char *));
	if (arst == NULL)
	{
		perror("cant allocate space");
		exit(1);
	}
	pars = _strtok(str, " ");
	while (pars != NULL)
	{
		while (pars[j])
		{
			if (pars[j] == '\n')
				pars[j] = '\0';
			j++;
		}
		arst[i] = pars;
		i++;
		j = 0;
		pars = _strtok(NULL, " ");
	}
	arst[i] = NULL;
	return (arst);
}


#include "shell.h"
/**
 * pathchk - check if command path is valid
 * @strr: command path
 * Return: 0 if false, otherwise 1
 */
int pathchk(char *strr)
{
	char *cmp = "/bin/", *ptr, *j;
	int i = 0, p = 0;

	ptr = malloc(sizeof(char) * MAX_COMMANDS);
	if (!ptr)
	{
		free(ptr);
		return (0);
	}
	while (cmp[i] != '\0')
	{
		if (cmp[i] != strr[i])
		{
			free(ptr);
			return (0);
		}
		i++;
	}
	while (strr[i] != '\0')
		ptr[p] = strr[i], p++, i++;

	ptr[p] = '\0';
	j = path(ptr);
	if (j)
	{
		free(ptr);
		return (1);
	}
	return (0);
}

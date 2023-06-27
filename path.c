#include "shell.h"

/**
 * path - check and create a path to the command
 * @strr: string to apply the check
 * Return: path to command or NULL if command is not found
 */
char *path(char *strr)
{
	DIR *dir = opendir("/bin/");
	char *tmp, *pth;
	struct dirent *entry;

	if (!dir)
		return (NULL);
	entry = readdir(dir);
	while (entry)
	{
		tmp = entry->d_name;
		if (_strcmp(tmp, strr) == 0)
		{
			pth = _strcat("/bin/", strr);
			closedir(dir);
			return (pth);
		}
		entry = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

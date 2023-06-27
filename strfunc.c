#include "shell.h"
/**
 * _strcat - concatenates string
 * @dest: dest parameter
 * @src: source parameter
 * Return: The concatenated string
 */
char *_strcat(char *dest, char *src)
{
	int a, b, c, i = 0, j = 0;
	char *new;

	a = _strlen(dest);
	b = _strlen(src);
	c = a + b + 1;
	new = malloc(sizeof(char) * c);
	if (new == NULL)
		return (NULL);

	for (i = 0; i < a; i++)
		new[i] = dest[i];

	while (j < b)
		new[i] = src[j], i++, j++;
	new[i] = '\0';
	return (new);
}
/**
 * _strcmp - compare two string
 * @fst: First string
 * @sec: Second string
 * Return: 0 if @fst and @sec are the same, otherwise 1
 */
int _strcmp(char *fst, char *sec)
{
	int i = 0, len;

	len = _strlen(fst);
	while (sec[i] != '\0')
	{
		if (sec[i] != fst[i])
			return (1);
		i++;
	}
	if (len != i)
		return (1);
	return (0);
}
/**
 * _strlen - computes the length of a string
 * @s: pointer to string
 * Return: returns the length of a string
 */
int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;
	return (i);
}
/**
 * _atoi - converts a string to an integer
 * @s: pointer to string
 * Return: 0 if no number in the string otherwise return number
 */
int _atoi(char *s)
{
	int index = 0;
	unsigned int num = 0;
	int mult = 1;
	int check = 0;

	while (s[index])
	{
		if (s[index] == '-')
			mult *= -1;
		while (s[index] >= '0' && s[index] <= '9')
		{
			check = 1;
			num = (num * 10) + (s[index] - '0');
			index++;
		}
		if (check == 1)
			index++;
	}
		num *= mult;
		return (num);
}

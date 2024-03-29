#include "shell.h"

int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);

/**
 * _strlen - Returns the length of a string
 * @s: A pointer to the characters string
 * Return: The length of the character string
 */
int _strlen(const char *s)
{
	int length = 0;

	if (!s)
		return (length);
	for (length = 0; s[length]; length++)
		;
	return (length);
}
/**
 *  _strcpy - Copies the string pointed to by src
 *  @dest: Pointer to the destination of copied string.
 *  @src: Pointer to the src of the source string.
 *  Return: Pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}
/**
 * _strcat - Concantenates two strings
 * @dest: Pointer to destination string
 * @src: Pointer to source string
 * Return: Pointer to destination string
 */
char *_strcat(char *dest, const char *src)
{
	char *destTmp;
	const char *srcTmp;

	destTmp = dest;
	srcTmp =  src;

	while (*destTmp != '\0')
		destTmp++;

	while (*srcTmp != '\0')
		*destTmp++ = *srcTmp++;
	*destTmp = '\0';
	return (dest);
}
/**
 * _strncat - Concantenates two strings where nmbr are copied from sourc
 * @dest: Pointer to destination string
 * @src: Pointer to source string
 * @n: n bytes to copy from src
 * Return: Pointer to destination string
 */
char *_strncat(char *dest, const char *src, size_t n)
{
	size_t dest_len = _strlen(dest);
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';

	return (dest);
}

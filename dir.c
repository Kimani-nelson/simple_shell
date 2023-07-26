#include "shell.h"

/**
 * wcount - counts the number of words in a string
 * @str: string to count words in
 * @delim: delimiters separating words
 *
 * Return: Number of words in the string, -1 on failure
 */

int wcount(char *str, char *delim)

{
	int count;
	char *dup;

	dup = str;
	if (str == NULL)
	{
		perror("Invalid String");
		return (-1);
	}

	strtok(dup, delim);
	for (count = 1; strtok(NULL, delim) != NULL; count++)
		;

	return (count);
}

/**
 * change_to_home - change the current working directory to home
 *
 * Return: 0 if successful, -1 otherwise
 */

int change_to_home(void)

{
	char *oldpwd, *pwd, buf[256];
	size_t size = 256;

	oldpwd = getcwd(buf, size);
	chdir(_getenv("HOME"));
	setenv("OLDPWD", oldpwd, 1);
	setenv("PWD", _getenv("PWD"), 1);

	return (0);
}

/**
 * change_to_previous - change the current working directory to the
 *                      previous one
 *
 * Return: 0 if successful, -1 otherwise
 */

int change_to_previous(void)

{
	char *oldpwd, *pwd, buf[256];
	size_t size = 256;

	if (_getenv("OLDPWD") == NULL)
	{
		perror("OLDPWD"); /* OLDPWD not set */
		return (-1);
	}
		else
	{
		oldpwd = getcwd(buf, size);
		chdir(_getenv("OLDPWD"));
		setenv("OLDPWD", oldpwd, 1); /* Update OLDPWD */
		pwd = getcwd(buf, size);
		setenv("PWD", pwd, 1);
	}

	return (0);
}

/**
 * change_dir - changes the current working directory and updates OLDPWD
 * @cmd: command to change the working directory
 *
 * Return: 0 if successful, -1 otherwise
 */

int change_dir(char *cmd)

{
	char *path, *dup, buf[256];
	int words;
	size_t size = 256;

	dup = _strdup(cmd);
	words = wcount(dup, " \t\r");
	if (words > 2)
	{
		_perror(cmd, "too many arguments");
		free(dup);
		dup = NULL;
		return (-1);
	}

	strtok(cmd, " \t\r");
	path = strtok(NULL, " ");

	if (path == NULL) /* home directory */
	{
		free(dup);
		dup = NULL;
		return (change_to_home());
	}

	if (_strcmp(path, "-") == 0)
	{
		free(dup);
		dup = NULL;
		return (change_to_previous());
	}

	if (change_directory(path) == -1)
	{
		free(dup);
		dup = NULL;
		return (-1);
	}

	return (0);
}

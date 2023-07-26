#include "shell.h"

/**
 * main - Entry point of the shell program
 *
 * Return: Always 0
 */

int main(void)

{
	char *line;
	int status;

	signal(SIGINT, SIG_IGN); /* Ignore Ctrl+C */

	while (1)
	{
		printf("($) ");
		line = read_line();

		if (line == NULL)
		{
			printf("\n");
			break;
		}

		status = execute_command(line);

		free(line);
	}

	return (0);
}

/**
 * read_line - Read a line of input from the user
 *
 * Return: The input line as a string, or NULL on failure or end of file
 */

char *read_line(void)

{
	char *line = NULL;
	size_t bufsize = 0;

	if (getline(&line, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
			return (NULL); /* End of file (Ctrl+D) */
		{
			perror("read_line");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

/**
 * execute_command - Execute a command entered by the user
 * @line: The command line entered by the user
 *
 * Return: Always 0
 */

int execute_command(char *line)

{
	line[strlen(line) - 1] = '\0'; /* Remove the trailing newline */

	if (strcmp(line, "exit") == 0)
		exit(EXIT_SUCCESS);

	printf("%s: command not found\n", line);

	return (0);
}

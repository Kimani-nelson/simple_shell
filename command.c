#include "shell.h"

/**
 * display_prompt - Display the shell prompt.
 */
void display_prompt(void)
{
	printf("$ ");
}

/**
 * read_command - Read a command line from the user.
 *
 * Return: The pointer to the input command line.
 */
char *read_command(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;

	characters_read = getline(&line, &bufsize, stdin);

	if (characters_read == -1)
	{
		if (feof(stdin))
		{
			/* Handle EOF (Ctrl+D) */
			putchar('\n');
			exit(sh_exit());
		}
		else
		{
			/* Handle read error */
			perror("read_command");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

/**
 * main - Entry point for the simple shell program.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *command_line;

	while (1)
	{
		display_prompt();
		command_line = read_command();
		/* Execute the command */
		printf("Executing: %s", command_line);
		free(command_line);
	}

	return (0);
}

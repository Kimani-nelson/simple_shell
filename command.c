#include "shell.h"

/**
 * display_prompt - Displays the shell prompt.
 */
void display_prompt(void)
{
	printf("$ ");
}

/**
 * read_command - Reads a command line from the user.
 *
 * Return: A pointer to the command line input or NULL on error.
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
			free(line);
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

/**
 * main - The main function that runs the shell.
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


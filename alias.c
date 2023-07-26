#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALIASES 100

/**
 * print_alias - Prints the alias with the specified name
 * @name: The name of the alias to print
 * @aliases: The array of aliases
 * @num_aliases: The number of aliases in the array
 */

static void print_alias(const char *name, char *aliases[], int num_aliases)

{
	int i;

	for (i = 0; i < num_aliases; i++)
	{
		char *alias = aliases[i];
		char *alias_name = strtok(alias, "=");
		char *alias_value = strtok(NULL, "=");

		if (strcmp(alias_name, name) == 0)
		{
			printf("%s='%s'\n", alias_name, alias_value);
			return;
		}
	}
}

/**
 * print_all_aliases - Prints all aliases
 * @aliases: The array of aliases
 * @num_aliases: The number of aliases in the array
 */

static void print_all_aliases(char *aliases[], int num_aliases)

{
	int i;

	for (i = 0; i < num_aliases; i++)
	{
		char *alias = aliases[i];
		char *alias_name = strtok(alias, "=");
		char *alias_value = strtok(NULL, "=");

		printf("%s='%s'\n", alias_name, alias_value);
	}
}

/**
 * add_alias - Adds an alias to the array
 * @name: The name of the alias
 * @value: The value of the alias
 * @aliases: The array of aliases
 * @num_aliases: The number of aliases in the array
 *
 * Return: 0 on success, -1 on failure
 */

static int add_alias(const char *name, const char *value,
		     char *aliases[], int *num_aliases)

{
	if (*num_aliases == MAX_ALIASES)
	{
		fprintf(stderr, "Error: Maximum number of aliases reached.\n");
		return (-1);
	}

	aliases[*num_aliases] = malloc(strlen(name) + strlen(value) + 2);
	if (aliases[*num_aliases] == NULL)
	{
		fprintf(stderr, "Error: Failed to allocate memory for alias.\n");
		return (-1);
	}

	sprintf(aliases[*num_aliases], "%s=%s", name, value);
	(*num_aliases)++;

	return (0);
}

/**
 * process_alias_command - Processes the alias command
 * @command: The command to process
 * @aliases: The array of aliases
 * @num_aliases: The number of aliases in the array
 */

static void process_alias_command(const char *command, char *aliases[], int *num_aliases)

{
	char *command_copy = strdup(command);
	char *token = strtok(command_copy, " \t=");
	const char *name;
	const char *value;

	if (token == NULL)
	{
		/* Print all aliases */
		print_all_aliases(aliases, *num_aliases);
	}
	else
	{
		name = token;
		token = strtok(NULL, " \t=");

		if (token == NULL)
		{
			/* Print specific alias */
			print_alias(name, aliases, *num_aliases);
		}
		else
		{
			value = token;

			/* Add or update alias */
			if (add_alias(name, value, aliases, num_aliases) == 0)
				printf("Alias added: %s='%s'\n", name, value);
		}
	}

	free(command_copy);
}

/**
 * main - Entry point of the program
 * @argc: The argument count
 * @argv: The argument vector
 *
 * Return: 0 on success, -1 on failure
 */

int main(int argc, char *argv[])

{
	char *aliases[MAX_ALIASES];
	int num_aliases = 0;
	int i;

	for (i = 1; i < argc; i++)
		process_alias_command(argv[i], aliases, &num_aliases);

	return (0);
}

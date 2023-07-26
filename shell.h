#ifndef SHELL_H
#define SHELL_H

/* Libraries */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

/* Constants */
#define BUF_SIZE 1024
#define DELIM " \t\r\n\a"
#define MAX_ARGS 64

/* Global Variables */
extern char **environ;

/* Function Prototypes */

/* Command.c */
void display_prompt(void);
char *read_command(void);

/* lines.c */
char **parse_arguments(char *line);

/* path.c */
char *find_path(char *command);

/* exit.c */
int sh_exit(void);

/* built.c */
int sh_env(void);

/* getline.c */
char *sh_getline(void);

/* strtok.c */
char *sh_strtok(char *str, const char *delim);

/* builtin.c */
int sh_exit_status(char **args);

/* setenv.c */
int sh_setenv(char **args);
int sh_unsetenv(char **args);

/* cd.c */
int sh_cd(char **args);

/* ;separator.c */
int sh_execute_with_separators(char *line);

/* logic.c */
int sh_execute_with_logic_operators(char *line);

/* alias.c */
int sh_alias(char **args);

/* Variables.c */
char *replace_variables(char *line);
char *replace_dollar_question(char *line);
char *replace_dollar_dollar(char *line);

/* Comments.c */
void remove_comments(char *line);

/* input.c */
int run_commands_from_file(char *filename);

#endif /* SHELL_H */

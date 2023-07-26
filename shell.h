#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/* Constants */
#define MAX_INPUT_LENGTH 1024
#define MAX_TOKENS 64
#define TOKEN_DELIMITERS " \t\r\n\a"
#define PROMPT "simple_shell$ "

/* Function Declarations */
void display_prompt(void);
char *read_line(void);
char **split_line(char *line);
void free_args(char **args);
int execute_command(char **args); /* Modify the function signature */
void handle_exit(char **args);
void handle_env(char **args);
void handle_cd(char **args);
void handle_setenv(char **args);
void handle_unsetenv(char **args);
void handle_alias(char **args);
void handle_separator(char **args);
void handle_logic(char **args);
void handle_variables(char **args);
void handle_comments(char **args);
void handle_input_file(const char *filename);
void handle_input(int argc, char **argv);
char **get_path(void);
int execute_pipeline(char **pipeline, int pipeline_length);
int execute_command_with_arguments(char **args);
char *build_path(char *path, char *command);
int check_command(char *command, char **paths);

#endif /* SHELL_H */

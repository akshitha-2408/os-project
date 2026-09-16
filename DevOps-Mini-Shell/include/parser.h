#ifndef PARSER_H
#define PARSER_H

#define MAX_ARGS 64

int parse_input(char *input, char **args);

int parse_command(char *input, char **args);

int split_pipe(char *input, char **left, char **right);

#endif

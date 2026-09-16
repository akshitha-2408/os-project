#include <string.h>
#include "parser.h"

int parse_input(char *input, char **args)
{
    int count = 0;

    char *token = strtok(input, " ");

    while (token != NULL && count < MAX_ARGS - 1)
    {
        args[count] = token;
        count++;

        token = strtok(NULL, " ");
    }

    args[count] = NULL;

    return count;
}

int parse_command(char *input, char **args)
{
    return parse_input(input, args);
}

int split_pipe(char *input, char **left, char **right)
{
    char *pipe_position = strchr(input, '|');

    if (pipe_position == NULL)
    {
        return 0;
    }

    *pipe_position = '\0';

    *left = input;
    *right = pipe_position + 1;

    return 1;
}

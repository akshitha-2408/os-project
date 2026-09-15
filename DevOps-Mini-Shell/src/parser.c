#include <string.h>
#include "parser.h"

int parse_input(char *input, char **args)
{
    int count = 0;

    char *token = strtok(input, " ");

    while(token != NULL && count < MAX_ARGS - 1)
    {
        args[count] = token;
        count++;

        token = strtok(NULL, " ");
    }

    args[count] = NULL;

    return count;
}

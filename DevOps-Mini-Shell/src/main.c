#include <stdio.h>
#include <string.h>
#include "input.h"
#include "parser.h"
#include "process.h"
#include "builtin.h"

int main()
{
    char input[1024];
    char *args[MAX_ARGS];

    while (1)
    {
        printf("myshell> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
        {
            continue;
        }

        parse_input(input, args);

        if (handle_builtin(args))
        {
            continue;
        }

        execute_command(args);
    }

    return 0;
}

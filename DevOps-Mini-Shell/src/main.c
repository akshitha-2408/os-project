#include <stdio.h>
#include <string.h>
#include "input.h"
#include "parser.h"

int main()
{
    char input[1024];
    char *args[MAX_ARGS];

    while(1)
    {
        printf("myshell> ");

        if(fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if(strcmp(input, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }

        if(strlen(input) == 0)
        {
            continue;
        }

        int count = parse_input(input, args);

        printf("Arguments: %d\n", count);

        for(int i = 0; i < count; i++)
        {
            printf("argv[%d] = %s\n", i, args[i]);
        }
    }

    return 0;
}

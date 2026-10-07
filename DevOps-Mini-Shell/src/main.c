#include <stdio.h>
#include <string.h>

#include "input.h"
#include "parser.h"
#include "process.h"
#include "builtin.h"
#include "signals.h"
#include "thread.h"

int main()
{
    char input[1024];

    char *args[MAX_ARGS];

    char *left_command;
    char *right_command;

    char *left_args[MAX_ARGS];
    char *right_args[MAX_ARGS];

    initialize_signals();
    start_monitor_thread();

    while (1)
    {
        printf("myshell> ");
        fflush(stdout);

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0)
        {
            continue;
        }

        if (split_pipe(input, &left_command, &right_command))
        {
            parse_command(left_command, left_args);
            parse_command(right_command, right_args);

            execute_pipeline(left_args, right_args);

            continue;
        }

        parse_input(input, args);

        int redirection_index = -1;
        int append = 0;

        for (int i = 0; args[i] != NULL; i++)
        {
            if (strcmp(args[i], ">") == 0)
            {
                redirection_index = i;
                append = 0;
                break;
            }

            if (strcmp(args[i], ">>") == 0)
            {
                redirection_index = i;
                append = 1;
                break;
            }
        }

        if (redirection_index != -1)
        {
            if (args[redirection_index + 1] == NULL)
            {
                printf("Redirection: missing filename\n");
                continue;
            }

            char *filename = args[redirection_index + 1];

            args[redirection_index] = NULL;

            execute_redirection(args, filename, append);

            continue;
        }

        if (handle_builtin(args))
        {
            continue;
        }

        execute_command(args);
    }

    return 0;
}

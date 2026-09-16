#include <stdio.h>
#include <string.h>

#include "input.h"
#include "parser.h"
#include "process.h"
#include "builtin.h"
#include "signals.h"


int main()
{
    char input[1024];

    char *args[MAX_ARGS];

    char *left_command;
    char *right_command;

    char *left_args[MAX_ARGS];
    char *right_args[MAX_ARGS];

    initialize_signals();

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


        /*
         * Check for pipe
         */

        if (split_pipe(input, &left_command, &right_command))
        {
            parse_command(left_command, left_args);
            parse_command(right_command, right_args);

            execute_pipeline(left_args, right_args);

            continue;
        }


        /*
         * Parse normal command
         */

        parse_input(input, args);


        /*
         * Check for input/output redirection
         *
         * >   = overwrite file
         * >>  = append to file
         * <   = read input from file
         */

        int redirection_index = -1;
        int append = 0;
        int input_redirect = 0;

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

            if (strcmp(args[i], "<") == 0)
            {
                redirection_index = i;
                input_redirect = 1;
                break;
            }
        }


        /*
         * If redirection is found
         */

        if (redirection_index != -1)
        {
            if (args[redirection_index + 1] == NULL)
            {
                printf("Redirection: missing filename\n");
                continue;
            }

            char *filename = args[redirection_index + 1];

            /*
             * Remove redirection operator
             * and filename from arguments
             */

            args[redirection_index] = NULL;


            /*
             * Input redirection
             */

            if (input_redirect)
            {
                execute_input_redirection(args, filename);
            }


            /*
             * Output redirection
             */

            else
            {
                execute_redirection(args, filename, append);
            }

            continue;
        }


        /*
         * Check built-in commands
         */

        if (handle_builtin(args))
        {
            continue;
        }


        /*
         * Execute external command
         */

        execute_command(args);
    }

    return 0;
}

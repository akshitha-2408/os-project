#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include "builtin.h"

int handle_builtin(char **args)
{
    if (args[0] == NULL)
    {
        return 1;
    }

    if (strcmp(args[0], "cd") == 0)
    {
        if (args[1] == NULL)
        {
            fprintf(stderr, "cd: missing argument\n");
        }
        else if (chdir(args[1]) != 0)
        {
            perror("cd");
        }

        return 1;
    }

    if (strcmp(args[0], "pwd") == 0)
    {
        char cwd[PATH_MAX];

        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("%s\n", cwd);
        }
        else
        {
            perror("pwd");
        }

        return 1;
    }

    if (strcmp(args[0], "help") == 0)
    {
        printf("Built-in commands:\n");
        printf("  cd <directory>  Change directory\n");
        printf("  pwd             Print current directory\n");
        printf("  help            Show this help message\n");
        printf("  clear           Clear the terminal\n");
        printf("  exit            Exit ShellForge\n");

        return 1;
    }

    if (strcmp(args[0], "clear") == 0)
    {
        printf("\033[H\033[J");
        return 1;
    }

    if (strcmp(args[0], "exit") == 0)
    {
        printf("Goodbye!\n");
        exit(0);
    }

    return 0;
}

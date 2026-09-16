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


    /* cd */

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


    /* pwd */

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


    /* help */

    if (strcmp(args[0], "help") == 0)
    {
        printf("\nShellForge Built-in Commands:\n");
        printf("  cd <directory>   Change directory\n");
        printf("  pwd              Show current directory\n");
        printf("  help             Show help\n");
        printf("  clear            Clear terminal\n");
        printf("  build            Build ShellForge\n");
        printf("  run              Run ShellForge\n");
        printf("  clean            Clean build files\n");
        printf("  gitstatus        Show Git status\n");
        printf("  exit             Exit ShellForge\n\n");

        return 1;
    }


    /* clear */

    if (strcmp(args[0], "clear") == 0)
    {
        printf("\033[H\033[J");
        return 1;
    }


    /* build */

    if (strcmp(args[0], "build") == 0)
    {
        printf("Building ShellForge...\n");

        system("make");

        return 1;
    }


    /* run */

    if (strcmp(args[0], "run") == 0)
    {
        printf("Starting ShellForge...\n");

        system("./bin/shellforge");

        return 1;
    }


    /* clean */

    if (strcmp(args[0], "clean") == 0)
    {
        printf("Cleaning build files...\n");

        system("make clean");

        return 1;
    }


    /* gitstatus */

    if (strcmp(args[0], "gitstatus") == 0)
    {
        printf("Git Status:\n");

        system("git status --short");

        return 1;
    }


    /* exit */

    if (strcmp(args[0], "exit") == 0)
    {
        printf("Goodbye!\n");
        exit(0);
    }


    return 0;
}

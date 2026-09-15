#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "process.h"

void execute_command(char **args)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return;
    }

    if (pid == 0)
    {
        execvp(args[0], args);

        perror("execvp failed");
        _exit(1);
    }
    else
    {
        waitpid(pid, NULL, 0);
    }
}

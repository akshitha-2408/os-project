#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <fcntl.h>

#include "process.h"


/*
 * Execute a normal external command
 */
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


/*
 * Execute two commands connected using a pipe
 *
 * Example:
 * ls | wc -l
 */
void execute_pipeline(char **left_args, char **right_args)
{
    int pipefd[2];

    if (pipe(pipefd) == -1)
    {
        perror("pipe failed");
        return;
    }

    /*
     * Create first child
     */
    pid_t pid1 = fork();

    if (pid1 < 0)
    {
        perror("fork failed");
        return;
    }

    if (pid1 == 0)
    {
        /*
         * First command writes to pipe
         */

        close(pipefd[0]);

        dup2(pipefd[1], STDOUT_FILENO);

        close(pipefd[1]);

        execvp(left_args[0], left_args);

        perror("execvp failed");
        _exit(1);
    }


    /*
     * Create second child
     */
    pid_t pid2 = fork();

    if (pid2 < 0)
    {
        perror("fork failed");
        return;
    }

    if (pid2 == 0)
    {
        /*
         * Second command reads from pipe
         */

        close(pipefd[1]);

        dup2(pipefd[0], STDIN_FILENO);

        close(pipefd[0]);

        execvp(right_args[0], right_args);

        perror("execvp failed");
        _exit(1);
    }


    /*
     * Parent closes both pipe ends
     */

    close(pipefd[0]);
    close(pipefd[1]);

    /*
     * Wait for both children
     */

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}


/*
 * Execute a command with output redirection
 *
 * >  = overwrite file
 * >> = append to file
 */
void execute_redirection(char **args, char *filename, int append)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return;
    }

    if (pid == 0)
    {
        int fd;

        /*
         * Append mode
         */
        if (append)
        {
            fd = open(
                filename,
                O_WRONLY | O_CREAT | O_APPEND,
                0644
            );
        }

        /*
         * Overwrite mode
         */
        else
        {
            fd = open(
                filename,
                O_WRONLY | O_CREAT | O_TRUNC,
                0644
            );
        }

        if (fd < 0)
        {
            perror("open failed");
            _exit(1);
        }

        /*
         * Redirect standard output to the file
         */
        dup2(fd, STDOUT_FILENO);

        close(fd);

        /*
         * Execute command
         */
        execvp(args[0], args);

        perror("execvp failed");
        _exit(1);
    }

    /*
     * Parent waits for child
     */
    waitpid(pid, NULL, 0);
}
void execute_input_redirection(char **args, char *filename)
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("fork failed");
        return;
    }

    if (pid == 0)
    {
        int fd = open(filename, O_RDONLY);

        if (fd < 0)
        {
            perror("open failed");
            _exit(1);
        }

        dup2(fd, STDIN_FILENO);
        close(fd);

        execvp(args[0], args);

        perror("execvp failed");
        _exit(1);
    }

    waitpid(pid, NULL, 0);
}

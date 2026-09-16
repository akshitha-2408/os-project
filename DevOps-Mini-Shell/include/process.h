#ifndef PROCESS_H
#define PROCESS_H

void execute_command(char **args);
void execute_pipeline(char **left_args, char **right_args);
void execute_redirection(char **args, char *filename, int append);
void execute_input_redirection(char **args, char *filename);

#endif

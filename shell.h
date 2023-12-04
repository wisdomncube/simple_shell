#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>

void enter_command(void);
char *user_input(char *executable, char *command, size_t size);
void execute_command(char *command);

#endif

#include "shell.h"

/**
 * findCtrlC - Handle the crtl + c call in prompt
 * @sig: Signal handler
 */
void findCtrlC(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n$ ", 3);
}

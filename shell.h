#ifndef _MAIN_H
#define _MAIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>

#define BUFSIZE 1024
#define TOK_BUFSIZE 128
#define TOK_DELIM " \t\r\n\a"

/* Points to an array of pointers to strings called the "environment" */
extern char **environ;


/**
 * struct data - struct that contains all relevant data on runtime
 * @av: argument vector
 * @input: command line written by the user
 * @args: tokens of the command line
 * @status: last status of the shell
 * @counter: lines counter
 * @_environ: environment variable
 * @pid: process ID of the shell
 */
typedef struct data
{
	char **av;
	char *input;
	char **args;
	int status;
	int counter;
	char **_environ;
	char *pid;
} shellData;

/**
 * struct listSeparator_s - single linked list
 * @separator: ; | &
 * @next: next node
 * Description: single linked list to store separators
 */
typedef struct listSeparator_s
{
	char separator;
	struct listSeparator_s *next;
} listSeparator;

/**
 * struct commandList_s - single linked list
 * @line: command line
 * @next: next node
 * Description: single linked list to store command lines
 */
typedef struct commandList_s
{
	char *line;
	struct commandList_s *next;
} commandList;

/**
 * struct rVar_list - single linked list
 * @len_var: length of the variable
 * @val: value of the variable
 * @len_val: length of the value
 * @next: next node
 * Description: single linked list to store variables
 */
typedef struct rVar_list
{
	int len_var;
	char *val;
	int len_val;
	struct rVar_list *next;
} rVar;

/**
 * struct builtin_s - Builtin struct for command args.
 * @name: The name of the command builtin i.e cd, exit, env
 * @f: data type pointer function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(shellData *datash);
} builtinCommands;

/* auxLists.c */
listSeparator *addSeparatorNodeEnd(listSeparator **head, char sep);
void freeListSeparator(listSeparator **head);
commandList *addLineNodeEnd(commandList **head, char *line);
void freeCommandList(commandList **head);

/* auxListsTwo.c */
rVar *addRVarNode(rVar **head, int lvar, char *var, int lval);
void freeRVarList(rVar **head);

/* auxString.c */
char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);

/* auxMemo.c */
void _memcpy(void *newptr, const void *ptr, unsigned int size);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size);

/* auxStringTwo.c */
char *_strdup(const char *s);
int _strlen(const char *s);
int compareChars(char str[], const char *delim);
char *_strtok(char str[], const char *delim);
int _isdigit(const char *s);

/* auxStringThree.c */
void reverseString(char *s);

/* findErrors.c */
int repeatedCharacter(char *input, int i);
int errorSeparateOpp(char *input, int i, char last);
int firstCharacter(char *input, int *i);
void displaySyntaxError(shellData *datash, char *input, int i, int bool);
int findSyntaxError(shellData *datash, char *input);

/* shellStartPoint.c */
char *noComment(char *in);
void shellStartingPoint(shellData *datash);

/* readLine.c */
char *readLine(int *i_eof);

/* tokenize.c */
char *swapCharacter(char *input, int bool);
void addNodes(listSeparator **head_s, commandList **head_l, char *input);
void nextNode(listSeparator **list_s, commandList **list_l, shellData *datash);
int tokenizeCommands(shellData *datash, char *input);
char **splitLine(char *input);

/* replaceVar.c */
void checkEnviron(rVar **h, char *in, shellData *data);
int checkVars(rVar **h, char *in, char *st, shellData *data);
char *replacedInput(rVar **head, char *input, char *new_input, int nlen);
char *replaceVariable(char *input, shellData *datash);

/* findLine.c */
void bringLine(char **lineptr, size_t *n, char *buffer, size_t j);
ssize_t getLine(char **lineptr, size_t *n, FILE *stream);

/* executeLine.c */
int executeLine(shellData *datash);

/* executeCommand.c */
int isChangeDir(char *path, int *i);
char *_which(char *cmd, char **_environ);
int isExecutable(shellData *datash);
int checkErrorCommand(char *dir, shellData *datash);
int executeCommand(shellData *datash);

/* environOne.c */
char *_getenv(const char *name, char **_environ);
int _env(shellData *datash);

/* environTwo.c */
char *copyInfo(char *name, char *value);
void setEnv(char *name, char *value, shellData *datash);
int _setenv(shellData *datash);
int _unsetenv(shellData *datash);

/* changeParentDir.c */
void changeDirDot(shellData *datash);
void changeDirTo(shellData *datash);
void changeDirPrev(shellData *datash);
void changeDirToHome(shellData *datash);

/* changeDir.c */
int changeDir(shellData *datash);

/* findBuiltIn.c */
int (*getBuiltIn(char *cmd))(shellData *datash);

/* exitShellProgram.c */
int exitShellProgram(shellData *datash);

/* auxLib.c */
int getLength(int n);
char *auxItoa(int n);
int _atoi(char *s);

/* auxErrorOne.c */
char *strCatCD(shellData *, char *, char *, char *);
char *errorGetCD(shellData *datash);
char *errorNotFound(shellData *datash);
char *errorExitShellProgram(shellData *datash);

/* auxErrorTwo.c */
char *errorGetAlias(char **args);
char *errorEnv(shellData *datash);
char *errorSyntax(char **args);
char *errorPerm(char **args);
char *errorPath(shellData *datash);


/* findError.c */
int findError(shellData *datash, int eval);

/* findCtrlC.c */
void findCtrlC(int sig);

/* auxAssist.c */
void auxHelpEnviron(void);
void auxHelpSetenv(void);
void auxHelpUnsetenv(void);
void auxHelpGen(void);
void auxHelpExit(void);

/* auxAssistTwo.c */
void auxHelp(void);
void auxHelpAlias(void);
void auxHelpCD(void);

/* findHelp.c */
int getHelp(shellData *datash);

#endif

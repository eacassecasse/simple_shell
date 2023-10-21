#ifndef MAIN_H
#define MAIN_H

#define EXEC 1
#define REDIR 2
#define PIPE 3
#define LIST 4

#define MAXARGS 1024
#define TOKENS "<|>;()"
#define WHITESPACE " \t\r\n\v"

#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

/**
 * struct cmd - structure for commands
 * @type: type of the command
 *
 * Description: Defines a structure for basic command
 *		which normally has a type
 */
typedef struct cmd
{
	int type;
} cmd_t;

/**
 * struct execcmd - structure for execution
 * @type: type of the command
 * @argv: list of command to execute
 * @eargv: list of options
 *
 * Description: Defines a structure for basic execution
 *		command, which has a type, a list of
 *		commands and a list of options
 */

typedef struct execcmd
{
	int type;
	char *argv[MAXARGS];
	char *eargv[MAXARGS];
} execcmd_t;

/**
 * struct redircmd - structure for I/O redirections
 * @type: type of the command
 * @cmd: command to execute
 * @file: source file from where to redirect
 * @efile: destination file to redirect
 * @mode: Type of redirection - I/O
 * @fd: File descriptor
 *
 * Description: Defines a structure for basic I/O
 *		Redirection, which includes source
 *		and destination files, mode of operation
 *		and file descriptor
 */
typedef struct redircmd
{
	int type;
	struct cmd *cmd;
	char *file;
	char *efile;
	int mode;
	int fd;
} redircmd_t;

/**
 * struct pipecmd - structure for Pipe Operations
 * @type: type of the command
 * @left: left node of the pipe
 * @right: right node of the pipe
 *
 * Description: Defines a structure for basic Pipe
 *		Operation, which has a type of command
 *		to execute, left node of the pipe
 *		and right node of the node
 */
typedef struct pipecmd
{
	int type;
	struct cmd *left;
	struct cmd *right;
} pipecmd_t;

/**
 * struct listcmd - structure for sequences
 * @type: type of the command
 * @left: left node of the sequence
 * @right: right node of the sequence
 *
 * Description: Defines a structure for basic sequencing
 *		execution, which has a type, a left node
 *		and a right node
 */
typedef struct listcmd
{
	int type;
	struct cmd *left;
	struct cmd *right;
} listcmd_t;

pid_t forkProcess(void);
struct cmd *parsepipe(char **ps, char *es);
struct cmd *parseline(char **ps, char *es);
struct cmd *parseblock(char **ps, char *es);
struct cmd *parseredirs(struct cmd *cmd, char **ps, char *es);
struct cmd *parseexec(char **ps, char *es);
void handleExec(struct cmd *cmd);
void handleRedir(struct cmd *cmd);
void handleSeq(struct cmd *cmd);
void handlePipe(struct cmd *cmd);
struct cmd *parsecmd(char *s);
struct cmd *nulterminate(struct cmd *cmd);
int peek(char **ps, char *es, char *toks);
int gettoken(char **ps, char *es, char **q, char **eq);
void eval(char *s, char *es, int *res, char *ws, char *sym);
int getcmd(char *buf, size_t nbuf);
void runcmd(struct cmd *cmd);
void error(const char *msg);
char *_memset(char *s, char b, unsigned int n);
int _putchar(char c);
void _puts(char *str);
int _strlen(char *s);
int _strcmp(const char *s1, const char *s2);
char *_strchr(char *s, char b);
struct cmd *execcmd(void);
struct cmd *redircmd(struct cmd *sc, char *f, char *ef, int mode, int fd);
struct cmd *pipecmd(struct cmd *left, struct cmd *right);
struct cmd *listcmd(struct cmd *left, struct cmd *right);

#endif

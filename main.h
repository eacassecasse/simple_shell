#ifndef MAIN_H
#define MAIN_H

#define BUF 1024
#define MAX_INPUT_CHARS 1000
#define MAX_ARGS 100
#define ALLOWED_COMMANDS "cd", \
	"exit", "ls", "touch", \
	"less", "vi", "vim"

#include <unistd.h>

char **parser(char *str, char *delim);
char **parseSeq(char *line);
char **parseLine(char *cmd);
pid_t forkProcess(void);
void readIn(char **buf);
void runCmd(char *filename, char *args[]);
void error(const char *msg);
int _putchar(char c);
void _puts(char *str);
int _strlen(char *s);
int _strcmp(const char *s1, const char *s2);

#endif

#ifndef SHELL_H
#define SHELL_H
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "strings.h"
#include "alias.h"
#include "builtins.h"
#include "inputs.h"
#include "helpers.h"
#include "history.h"
#include "file_mode.h"

extern char **environ;
void sigint_handler(int sig);
char *logical_and(char *);
char *logical_or(char *);
char **parse_command(char *, char *);
char *get_full_path(char *);
char *find_path(char *, char *, char **);
int execute(char **, char **);
void exec_builtin(int, char **);
#endif

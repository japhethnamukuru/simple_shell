#ifndef INPUTS_H
#define INPUTS_H
ssize_t get_input(char **, char **, char **);
char *check_separator(char *);
void expand_vars(char **);
void free_args(char **);
void free_args_exit(char **);

#endif

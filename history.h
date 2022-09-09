#ifndef HISTORY_H
#define HISTORY_H
int read_history(void);
int display_history(char **);
int add_to_history(char *);
int write_history(void);
char **get_history(void);

#endif

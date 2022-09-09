#ifndef ALIAS_H
#define ALIAS_H
int aliasing(char **args);
char **set_alias(char *arg, char **);
char *find_alias(char *alias, char **);
char **add_alias(char *alias, char **, int overwrite);
char **get_aliases(void);

#endif

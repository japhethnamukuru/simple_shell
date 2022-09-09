#ifndef STRINGS_H
#define STRINGS_H
int str_cmp(char *s1, char *s2);
int str_ncmp(char *s1, char *s2, size_t n);
size_t str_len(char *s);
char *mem_cpy(char *dest, const char *src, size_t n);
char *str_dup(char *s);
char *str_tok(char *str, char *delim);
char *str_tok_r(char *str, char *delim, char **save_ptr);
ssize_t mygetline(char **buff, size_t *n, FILE *stream);

#endif

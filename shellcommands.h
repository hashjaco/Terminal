#ifndef SHELLCOMMANDS_H
#define SHELLCOMMANDS_H

int myshell_launch(char **args);
char **myshell_parse_input(char * input);
char *myshell_read_input(void);
int number_of_builtins();
int myshell_cd(char **args);
int myshell_ls(char **args);
int myshell_pwd(char **args);
int myshell_clear(char **args);
int myshell_grep(char **args);
int myshell_cat(char **args);
int myshell_exit(char **args);


#endif

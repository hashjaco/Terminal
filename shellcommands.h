#ifndef SHELLCOMMANDS_H
#define SHELLCOMMANDS_H

void myshell_loop(char **args);
int myshell_launch(char **args);
int myshell_execute(char **args);
char **myshell_parse_input(char * input);
char *myshell_read_input(void);
int number_of_builtins();
int myshell_cd(char **args);
int myshell_pwd(char **args);
int myshell_pipe(char **args);
int myshell_redirectO(char **args);
int myshell_redirectI(char **args);
int myshell_exit(char **args);

#endif

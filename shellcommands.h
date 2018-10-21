#ifndef SHELLCOMMANDS_H
#define SHELLCOMMANDS_H

int getNumberOfBuiltinCommands();
int myshell_cd(char **args);
int myshell_ls(char **args);
int myshell_pwd(char **args);
int myshell_clear(char **args);
int myshell_grep(char **args);
int myshell_cat(char **args);
int myshell_exit(char **args);


#endif

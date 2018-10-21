char *builtin_commands[] = {
	"cd",
	"pwd"
}

int (*builtin_functions[])(char **) = {
	&myshell_cd,
	&myshell_pwd
}

int getNumberOfBuiltinCommands(){
	return sizeof(builtin_commands) / sizeof(char *);
}

int myshell_cd(char **args){}
int myshell_ls(char **args){}
int myshell_pwd(char **args){}
int myshell_clear(char **args){}
int myshell_grep(char **args){}
int myshell_cat(char **args){}
int myshell_exit(char **args){
	return 0;
}
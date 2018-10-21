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

int myshell_cd(char **args){
	if (args[1] == NULL) fprintf(stderr, "myshell: expected argument to \"cd\"\n");
	else 
		if (chdir(args[1]) != 0) perror("Error changing directory\n");
	return 1;
}
int myshell_ls(char **args){

}
int myshell_pwd(char **args){}
int myshell_clear(char **args){}
int myshell_grep(char **args){}
int myshell_cat(char **args){}
int myshell_exit(char **args){
	return 0;
}
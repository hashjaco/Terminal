#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "shellcommands.h"
#define BUFFER_SIZE 256
#define DELIMITER " "
#define _GNU_SOURCE
#define PROMPT "MyShell => "


typedef struct Builtin{
	char* name;
	int (*func)(char**);
} Builtin;

Builtin builtins[7]{
	{"cd", &myshell_cd},
	{"pwd", &myshell_pwd},
	{"ls", &myshell_ls},
	{"exit", &myshell_exit},
	{"cat", &myshell_cat},
	{"grep", &myshell_grep},
	{"clear", &myshell_clear}
};

char *builtin_commands[] = {
	"cd",
	"pwd",
	"ls",
	"exit",
	"cat",
	"grep",
	"clear"
};

int (*builtin_functions[])(char **) = {
	&myshell_cd,
	&myshell_pwd,
	&myshell_ls,
	&myshell_exit,
	&myshell_cat,
	&myshell_grep,
	&myshell_clear
};

int number_of_builtins()
{
	return sizeof(builtins) / sizeof(char *);
}

char *myshell_read_input(void)
{
	char *input = NULL;
	ssize_t buffer_size = 0;
    fgets(input,BUFFER_SIZE,stdin); // Get user input
	return input;
}

char **myshell_parse_input(char * input)
{
	int buffer_size = BUFFER_SIZE, position = 0;
	char **tokens = malloc(buffer_size * sizeof(char*));
	char *token;
	if (!tokens) {
		fprintf(stderr, "MyShell: Allocation Error!\n");
		exit(EXIT_FAILURE);
	}
	token = strtok(input, DELIMITER); // Parse string into array
    while(token != NULL){
        tokens[position] = token;
        position++;

        if (position >= buffer_size) {
        	buffer_size += BUFFER_SIZE;
        	tokens = realloc(tokens, buffer_size + sizeof(char*));
        	if (!tokens){
        		fprintf(stderr, "MyShell: Allocation Error!\n");
        		exit(EXIT_FAILURE);
        	}
        }

        token = strtok(NULL, DELIMITER);
    }
    tokens[position] = NULL;
    return tokens;
}

char **

int myshell_launch(char **args)
{
	pid_t parent, child;
	int status;
	child = fork(); // Create child process
	  // parent wait for child to return execution
	  // Create pipe between child and parent process
	  // Child process should execute command and return output to parent process before being freed
	  if (child < 0) // Fork failed
	  {
	      perror("Fork failed\n"); // Error message
	  }
	  else if (child == 0) // Child process
	  { 
	    if (execvp(args[0],args) == -1) perror("Error executing program.\n");
	    printf("Child process is executing command...\n"); 
	    sleep(5); 
	    printf("Child process has finished executing.\n");
	    exit(EXIT_FAILURE);
	  }
	  else { 
	  // Parent process
	    do {
	      parent = waitpid(child, &status, WUNTRACED);
	    } while(!WIFEXITED(status) && !WIFSIGNALED(status));
	  }

  return 1;
}

int myshell_execute(char **args)
{
	int i;

	if (args[0] == NULL){
		// Empty command
		return 1;
	}

	for (i=0; i < number_of_builtins(); i++){
		if (strcmp(args[0], builtins[i].name) == 0) return (*builtins[i].func)(args);
	}

	return myshell_launch(args);
}

void myshell_loop(void)
{
	char *input;
	char **args;
	int status;

	do {
		printf(PROMPT);
		input = myshell_read_input();
		args = myshell_parse_input(input);
		status = myshell_execute(args);

		free(input);
		free(args);
	} while (status);
}

int myshell_cd(char **args)
{
	if (args[1] == NULL) fprintf(stderr, "MyShell: Expected argument to \"cd\"\n");
	else 
		if (chdir(args[1]) != 0) perror("Error changing directory\n");
	return 1;
}

int myshell_ls(char **args)
{
	opendir(myshell_pwd());
	readdir(myshell_pwd());
	closedir(myshell_pwd());
	return 1;
}

int myshell_pwd(){

	int pwd;
	pwd = getcwd(NULL, 0);
	return pwd;
}

int myshell_clear(char **args){
	return clear();
}

int myshell_grep(char **args){
	if (args[1] == NULL) fprintf(stderr, "MyShell: Missing argument\n"); return -1;
	return grep(args[1]);
}
int myshell_cat(char **args){}
int myshell_exit(char **args){
	return 0;
}
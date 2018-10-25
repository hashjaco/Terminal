#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include "shellcommands.h"
#define BUFFER_SIZE 256
#define DELIMITER " \n"
#define _GNU_SOURCE
#define PROMPT "MyShell => "

char * buffer;

typedef struct Built_in {
	char* name;
	int (*func)(char**);
} Built_in;

Built_in built_ins[] = {
	{"cd", &myshell_cd},
	{"pwd", &myshell_pwd},
	{"exit", &myshell_exit}
};

int number_of_builtins()
{
	return sizeof(built_ins) / (sizeof(char *)*2);
}

char *myshell_read_input(void)
{
	char *input = NULL;
	ssize_t buffer_size = 0;
    getline(&input, &buffer_size, stdin); // Get user input
    if (strcmp(input,"exit\n") == 0) exit(1);
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
    while(token != NULL) {
        tokens[position] = token;
        position++;

        if (position >= buffer_size) {
        	buffer_size += BUFFER_SIZE;
        	tokens = realloc(tokens, buffer_size * sizeof(char*));
        	if (!tokens) {
        		fprintf(stderr, "MyShell: Allocation Error!\n");
        		exit(EXIT_FAILURE);
        	}
        }
        token = strtok(NULL, DELIMITER);
    }
    tokens[position] = NULL;
    
    return tokens;
}


int myshell_launch(char **args)
{
	int status;
	
	pid_t pid = fork(); // Create child process
	  // parent wait for child to return execution
	  // Child process should execute command, return output to parent process, and die!
	  if (pid < 0) {
	    printf("Fork failed\n"); 
	    exit(1);
	  }

	  else if (pid > 0) waitpid(-1,&status,0);

	// Child process
	  else {
	    if (execvp(*args,args) < 0) { 
		    perror("Error executing program\n"); 
		    exit(1); 
	    }
	  }

  return 1;
}

int myshell_execute(char **args)
{
	int i;

	if (args[0] == NULL){
		printf("No command given\n");
		exit(1);
	}
	for (i=0; i < (number_of_builtins()); i++){
		if (strcmp(args[0], built_ins[i].name) == 0) {
		   return (*built_ins[i].func)(args);
		}
	}
	return myshell_launch(args);
}

void myshell_loop(char **args)
{
	char *input;
	int status;

	do {
		printf("%s =>  ", getcwd(buffer,BUFFER_SIZE));
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
	else {
	  if (chdir(args[1]) != 0) { 
	       perror("Error changing directory\n"); 
	       exit(1); 
	  }
	}
	return 1;
}


int myshell_pwd(char **args)
{
	buffer = getcwd(buffer,BUFFER_SIZE);
        if (buffer == NULL) { 
	    printf("Error printing current directory\n"); 
	    exit(1); 
	}
	printf("%s\n",buffer);
	free(buffer);
	return 1;
}

int myshell_exit(char **args) { 
	return 0; 
}

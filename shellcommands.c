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


typedef struct Built_in {
	char* name;
	int (*func)(char**);
} Built_in;

Built_in built_ins[7] = {
	{"cd", &myshell_cd},
	{"pwd", &myshell_pwd},
	{"ls", &myshell_ls},
	{"exit", &myshell_exit},
	{"cat", &myshell_cat},
	{"grep", &myshell_grep},
	{"clear", &myshell_clear}
};

char *built_in_commands[] = {
	"cd",
	"pwd",
	"ls",
	"exit",
	"cat",
	"grep",
	"clear"
};

int (*built_in_functions[])(char **) = {
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
	return sizeof(built_ins) / (sizeof(char *)*2);
}

char *myshell_read_input(void)
{
	char *input = NULL;
	ssize_t buffer_size = 0;
    getline(&input, &buffer_size, stdin); // Get user input
    printf("Reading input...\n"); sleep(5);
	return input;
}

char **myshell_parse_input(char * input)
{
	printf("Parsing input...\n"); sleep(5);
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
        	tokens = realloc(tokens, buffer_size * sizeof(char*));
        	if (!tokens){
        		fprintf(stderr, "MyShell: Allocation Error!\n");
        		exit(EXIT_FAILURE);
        	}
        }

        token = strtok(NULL, DELIMITER);
    }
    tokens[position] = NULL;
    printf("Finished parsing\n");
    return tokens;
}


int myshell_launch(char **args)
{
	printf("Launching program...\n"); sleep(5);
	pid_t parent, child;
	int status;
	child = fork(); // Create child process
	  // parent wait for child to return execution
	  // Create pipe between child and parent process
	  // Child process should execute command and return output to parent process before being freed
	  
	  if (child == 0) // Child process
	  { 
	    if (strcmp(args[0],"cd")==0) {
	       if (chdir(args[1]) < 0){printf("Directory not found.");}
	    }
	    char* file = strcat("/bin/",args[0]);
	    if (execvp(file, args) < 0)
	    { 
		perror("Error executing program.\n"); exit(1); 
	    }
	    printf("Child process is executing command...\n"); 
	    sleep(5); 
	    printf("Child process has finished executing.\n");
	    exit(EXIT_FAILURE);
	  }
	  else if (child < 0)
	  {
	    printf("There was an error forking\n"); exit(-1);		  
	  }
	  else 
	  { 
	  // Parent process
	    do 
	    {
	      parent = waitpid(child, &status, WUNTRACED);
	    } while(!WIFEXITED(status) && !WIFSIGNALED(status));
	  }
	  printf("Finished launching\n");

  return 1;
}

int myshell_execute(char **args)
{
	printf("Executing program...\n"); sleep(1);
	int i;

	if (args[0] == NULL){
		// Empty command
		return 1;
	}

	printf("args[0] is not empty\n"); sleep(1);

	for (i=0; i < (number_of_builtins()-1); i++){
		printf("There are %d elements in built-ins array\n",number_of_builtins()); sleep(1);
		printf("Comparing argument %d: %s with built-in command #%d: %s...\n",0,args[0],i,built_ins[i].name);
		if (strcmp(args[0], built_ins[i].name) == 0) 
			return (*built_ins[i].func)(args);
	}
	printf("Executed successfully\n");
	return myshell_launch(args);
}

void myshell_loop(char **args)
{
	printf("Initiating Loop...\n"); sleep(1);
	char *input;
	int status;

	do {
		printf(PROMPT);
		input = myshell_read_input();
		args = myshell_parse_input(input);
		status = myshell_execute(args);

		free(input);
		free(args);
	} while (status);
	printf("Loop complete\n");
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
	return 1;
}

int myshell_pwd(char **args){

	char * pwd = getcwd(NULL, 0);
	return 0;
}

int myshell_clear(char **args){
	return 1;
}

int myshell_grep(char **args){
	if (args[1] == NULL) fprintf(stderr, "MyShell: Missing argument\n"); return -1;
	return 1;
}


int myshell_cat(char **args){ return 0; }
int myshell_exit(char **args){
	return 0;
}

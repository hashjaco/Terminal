/****************************************************************
 * Name        : Hashim Jacobs                                  *
 * Class       : CSC 415                                        *
 * Date        : 10/5/2018                                      *
 * Description :  Writing a simple bash shell program           *
 *                that will execute simple commands. The main   *
 *                goal of the assignment is working with        *
 *                fork, pipes and exec system calls.            *
 ****************************************************************/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include "shellcommands.h"

#define _GNU_SOURCE
#define BUFFER_SIZE 256
#define PROMPT "MyShell => "

int main(int argc, char*argv[])
{
  char COMMAND[BUFFER_SIZE];
  const char delimiter[2] = " ";
  char * buffer;
  char * directory;
  int status;
  argc = 0;

  printf("*************TERMINAL*************\n");

  while(1) // While program is running
  {
    printf(PROMPT); // Prompt for input
    fgets(COMMAND,BUFFER_SIZE,stdin); // Get user input
    printf("%s\n",COMMAND); // Print user input
    if (strcmp(COMMAND,"exit\n")==0) exit(1); // Exit if user input = exit
    *argv = strtok(COMMAND,delimiter); // Parse string into array
    while(*argv!=NULL){
        ++argc;
        *argv = strtok(NULL,delimiter);
        printf("%s\n",*argv);
    }
      printf("%d\n",argc);

      pid_t parent, child;
      child = fork(); // Create child process
      // parent wait for child to return execution
      // Create pipe between child and parent process
      // Child process should execute command and return output to parent process before being freed
      if (child < 0) // Fork failed
      {
          perror("Fork failed\n"); exit(-1); // Error message
      }
      else if (child == 0) // Child process
      { 
        if (execvp(argv[0],argv) == -1) perror("Error executing program.\n");
        printf("Child process is executing command...\n"); 
        sleep(5); 
        printf("Child process has finished executing.\n");
        exit(EXIT_FAILURE);
      }
      else { // Parent process
        do {
          parent = waitpid(child, &status, WUNTRACED);
        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
      }
      
  }
  return 1;
}
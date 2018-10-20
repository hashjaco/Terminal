/****************************************************************
 * Name        : Hashim Jacobs                                  *
 * Class       : CSC 415                                        *
 * Date        : 10/5/2018                                      *
 * Description :  Writing a simple bash shell program           *
 *                that will execute simple commands. The main   *
 *                goal of the assignment is working with        *
 *                fork, pipes and exec system calls.            *
 ****************************************************************/

#define _GNU_SOURCE
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFFER_SIZE 256
#define PROMPT "MyShell => "

int main(int argc, char*argv[])
{
  char COMMAND[BUFFER_SIZE];
  const char delimiter[2] = " ";
  char * buffer;
  char * directory;
  argc = 0;

  printf("*************TERMINAL*************\n");

  while(1) // While program is running
  {
    printf(PROMPT); // Prompt for input
    fgets(COMMAND,BUFFER_SIZE,stdin); // Get user input
    printf("%s",COMMAND); // Print user input
    if (strcmp(COMMAND,"exit\n")==0) exit(1); // Exit if user input = exit
      *argv = strtok(COMMAND,delimiter);
      ++argc;
    while(*argv!=NULL){
      *argv = strtok(NULL,delimiter);
      }
      printf("%d",argc);


      pid_t process = fork(); // Create child process
      // parent wait for child to return execution
      // Create pipe between child and parent process
      // Child process should execute command and return output to parent process before being freed
      if (child_process < 0)
      {
          perror("Fork failed\n"); exit(-1); // Error message
      }
      pid_t pipeBetweenProcesses[2] = {child_process,parent_process};
      pipe2(pipeBetweenProcesses,O_CLOEXEC);
      

  }

}

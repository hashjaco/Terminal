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

#define BUFFERSIZE 256
#define PROMPT "MyShell => "
#define PROMPTSIZE sizeof(PROMPT)
#define EXIT "exit\n"

int main(int* argc, char** argv)
{
  char COMMAND[BUFFERSIZE];
  char* buffer;
  char* directory;

printf("*************TERMINAL*************\n");

do
{
  printf(PROMPT);
  scanf("%s",COMMAND);
  printf("%s\n",COMMAND);
} while(COMMAND!=EXIT);
    
return 0;
}

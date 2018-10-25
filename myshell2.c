#include "shellcommands.h"
#include <stdio.h>

int main(int argc, char **argv)
{
// Begin terminal loop
	myshell_loop(argv);
	printf("Program complete\n");
	return 0;
}

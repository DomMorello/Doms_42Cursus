#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
	printf("test start!!!!\n");

	execve("sub", NULL, NULL);

	printf("workign??\n");
	return 0;
}

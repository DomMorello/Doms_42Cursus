#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int x =0;

	pid_t pid = fork();
	printf("%d %d\n", getpid(), pid);
	while (1)
	{
		
	}
	return 0;
}

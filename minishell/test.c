#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
	char *str = getcwd(NULL, 255);
	printf("%s\n", str);
	return 0;
}

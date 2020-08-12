#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

char *alloc(void)
{
	char *ret;

	ret = malloc(10);
	return ret;
}

int main(int argc, char *argv[])
{
	char *s = getcwd(NULL, 0);
	printf("%s\n", s);
	int ret = chdir("..");
	s = getcwd(NULL, 0);
	printf("%s\n", s);
	return 0;
}

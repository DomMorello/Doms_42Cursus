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
//	char buf[5];

	char *buf = getcwd(buf, 1);
	char *err = strerror(errno);
	printf("error: %s\n", err);
	printf("%s\n", buf);
	buf = NULL;
	while (1)
	{
		;
	}
	return 0;
}

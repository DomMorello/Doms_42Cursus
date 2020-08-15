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
	int fd = open("note.md", O_RDONLY);
	printf("fd%d\n", fd);
	char buf[10];
	int ret = read(fd, buf, sizeof(buf));
	printf("%s\n", buf);
	int fd2 = dup2(fd, fd2);
	printf("fd2:%d\n", fd2);
	ret = read(fd2, buf, sizeof(buf));
	printf("%s\n", buf);


	close(fd);

	return 0;
}

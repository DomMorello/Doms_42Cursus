#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int main(int argc, char const *argv[])
{
    struct timeval mytime;

    gettimeofday(&mytime, NULL);
    printf("%ld:%ld\n", mytime.tv_sec, mytime.tv_usec);

    return 0;
}

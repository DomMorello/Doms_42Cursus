#include "./philo_three.h"

void child_p(void)
{
    printf("child 1 going...\n");
}

int main(int argc, char const *argv[])
{
    int stat;

    printf("main start:\n");
    pid_t pid = fork();
    if (pid == 0)
    {
        child_p();
    }
    waitpid(pid, &stat, WNOHANG);
    printf("hihi\n");
    return 0;
}

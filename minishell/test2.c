#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

extern char **environ;
int main(int argc, char *argv[])
{
    char **new_argv;
    char command[] = "ls";
    int idx;
    new_argv = (char **)malloc(sizeof(char *) * (argc + 1)); /* ��ɾ ls�� ���� */
    new_argv[0] = command;                                   /* command line���� �Ѿ�� parameter�� �״�� ��� */
    for (idx = 1; idx < argc; idx++)
    {
        new_argv[idx] = argv[idx];
    } /* argc�� execve �Ķ���Ϳ� ������ �� ���� ������ NULL�� �Ķ������ ���� �ǹ��� */
    new_argv[argc] = NULL;
    if (execve("/usr/bin/ls", new_argv, environ) == -1)
    {
        fprintf(stderr, "���α׷� ���� error: %s\n", strerror(errno));
        return 1;
    } /* ls ��ɾ� binary�� ��������� ��ü�Ǿ����Ƿ� ������ ������ ���� ������� �ʽ��ϴ�. */
    printf("�̰��� ���� ls ��ɾ�� �� ������ ����� ���� �ʽ��ϴ�.\n");
    return 0;
}

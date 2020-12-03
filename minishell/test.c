#include "minishell.h"

int g_pipe_fd[2];
int g_red_out_fd;
int g_red_in_fd;

t_list *g_env_list;
t_list g_env_head;

extern char **environ;

void set_red_in(char *title)
{
	g_red_in_fd = open(title, O_CREAT | O_RDWR);
	dup2(g_red_in_fd, 0);
	close(g_red_in_fd);
}

void set_red_out(char *title)
{
	g_red_out_fd = open(title, O_CREAT | O_RDWR);
	dup2(g_red_out_fd, 1);
	close(g_red_out_fd);
}

void test()
{
	// grep Sep < hello1 | wc > hello2
	pipe(g_pipe_fd);

	pid_t pid = fork();
	wait(NULL);
	if (pid == 0)
	{
		close(g_pipe_fd[0]);
		dup2(g_pipe_fd[1], 1);
		close(g_pipe_fd[1]);
		set_red_in("./hello");
		execlp("grep", "grep", "Sep", NULL);
	}
	else
	{
		close(g_pipe_fd[1]);
		dup2(g_pipe_fd[0], 0);
		close(g_pipe_fd[0]);
		set_red_out("./hello1");
		execlp("wc", "wc", NULL);
	}
}

void copy_environ(void)
{
	int i;
	t_list *tmp;

	g_env_head.content = ft_strdup(environ[0]);
	g_env_head.next = NULL;
	g_env_list = &g_env_head;
	i = 1;
	while (environ[i])
	{
		tmp = ft_lstnew(ft_strdup(environ[i]));
		ft_lstadd_back(&g_env_list, tmp);
		i++;
	}
}

void sig_handler(int signo)
{
	printf("worked!\n");
	exit(1);
}

struct NODE {    // ���� ����Ʈ�� ��� ����ü
    struct NODE *next;    // ���� ����� �ּҸ� ������ ������
    int data;             // �����͸� ������ ���
};

void addFirst(struct NODE *target, int data)    // ���� ��� �ڿ� ��带 �߰��ϴ� �Լ�
{
    struct NODE *newNode = malloc(sizeof(struct NODE));    // �� ��� ����
    newNode->next = target->next;    // �� ����� ���� ��忡 ���� ����� ���� ��带 ����
    newNode->data = data;            // ������ ����

    target->next = newNode;    // ���� ����� ���� ��忡 �� ��带 ����
}

void removeFirst(struct NODE *target)    // ���� ����� ���� ��带 �����ϴ� �Լ�
{
    struct NODE *removeNode = target->next;    // ���� ����� ���� ��� �ּҸ� ����
    target->next = removeNode->next;     // ���� ����� ���� ��忡 ������ ����� ���� ��带 ����

    free(removeNode);    // ��� �޸� ����
}

int main()
{
    struct NODE *head = malloc(sizeof(struct NODE));    // �Ӹ� ��� ����
                                                        // �Ӹ� ���� �����͸� �������� ����
    head->next = NULL;

    addFirst(head, 10);      // �Ӹ� ��� �ڿ� �� ��� �߰�
    addFirst(head, 20);      // �Ӹ� ��� �ڿ� �� ��� �߰�
    addFirst(head, 30);      // �Ӹ� ��� �ڿ� �� ��� �߰�

    removeFirst(head);       // �Ӹ� ��� �ڿ� �ִ� ��带 ����

    struct NODE *curr = head->next;                                                                      
    // ���� ����Ʈ ��ȸ�� �����Ϳ� ù ��° ����� �ּ� ����
    while (curr != NULL)                // �����Ͱ� NULL�� �ƴ� �� ��� �ݺ�
    {
        printf("%d\n", curr->data);     // ���� ����� ������ ���
        curr = curr->next;              // �����Ϳ� ���� ����� �ּ� ����
    }

    curr = head->next;      // ���� ����Ʈ ��ȸ�� �����Ϳ� ù ��° ����� �ּ� ����
    while (curr != NULL)    // �����Ͱ� NULL�� �ƴ� �� ��� �ݺ�
    {
        struct NODE *next = curr->next; // ���� ����� ���� ��� �ּҸ� �ӽ÷� ����
        free(curr);        // ���� ��� �޸� ����
        curr = next;       // �����Ϳ� ���� ����� �ּ� ����
    }

    free(head);    // �Ӹ� ��� �޸� ����

    return 0;
}

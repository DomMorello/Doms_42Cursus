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

struct NODE {    // 연결 리스트의 노드 구조체
    struct NODE *next;    // 다음 노드의 주소를 저장할 포인터
    int data;             // 데이터를 저장할 멤버
};

void addFirst(struct NODE *target, int data)    // 기준 노드 뒤에 노드를 추가하는 함수
{
    struct NODE *newNode = malloc(sizeof(struct NODE));    // 새 노드 생성
    newNode->next = target->next;    // 새 노드의 다음 노드에 기준 노드의 다음 노드를 지정
    newNode->data = data;            // 데이터 저장

    target->next = newNode;    // 기준 노드의 다음 노드에 새 노드를 지정
}

void removeFirst(struct NODE *target)    // 기준 노드의 다음 노드를 삭제하는 함수
{
    struct NODE *removeNode = target->next;    // 기준 노드의 다음 노드 주소를 저장
    target->next = removeNode->next;     // 기준 노드의 다음 노드에 삭제할 노드의 다음 노드를 지정

    free(removeNode);    // 노드 메모리 해제
}

int main()
{
    struct NODE *head = malloc(sizeof(struct NODE));    // 머리 노드 생성
                                                        // 머리 노드는 데이터를 저장하지 않음
    head->next = NULL;

    addFirst(head, 10);      // 머리 노드 뒤에 새 노드 추가
    addFirst(head, 20);      // 머리 노드 뒤에 새 노드 추가
    addFirst(head, 30);      // 머리 노드 뒤에 새 노드 추가

    removeFirst(head);       // 머리 노드 뒤에 있는 노드를 삭제

    struct NODE *curr = head->next;                                                                      
    // 연결 리스트 순회용 포인터에 첫 번째 노드의 주소 저장
    while (curr != NULL)                // 포인터가 NULL이 아닐 때 계속 반복
    {
        printf("%d\n", curr->data);     // 현재 노드의 데이터 출력
        curr = curr->next;              // 포인터에 다음 노드의 주소 저장
    }

    curr = head->next;      // 연결 리스트 순회용 포인터에 첫 번째 노드의 주소 저장
    while (curr != NULL)    // 포인터가 NULL이 아닐 때 계속 반복
    {
        struct NODE *next = curr->next; // 현재 노드의 다음 노드 주소를 임시로 저장
        free(curr);        // 현재 노드 메모리 해제
        curr = next;       // 포인터에 다음 노드의 주소 저장
    }

    free(head);    // 머리 노드 메모리 해제

    return 0;
}

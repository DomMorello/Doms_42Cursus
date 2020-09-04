#include "minishell.h"

extern char **environ;

# define PWD "PWD="
# define OLDPWD "OLDPWD="

static int	ft_isspace(char c)
{
	if (c == '\t' || c == ' ')
		return (TRUE);
	return (FALSE);
}

int update_cwd(t_list **list)
{
	t_list *tmp;
	char *cur_cwd;
	char buf[100];

	tmp = *list;
	cur_cwd = getcwd(buf, sizeof(buf));
	while (tmp)
	{
		if (!ft_strncmp((char *)tmp->content, PWD, ft_strlen(PWD)))
			ft_strlcpy(tmp->content + ft_strlen(PWD), cur_cwd, ft_strlen(cur_cwd) + 1);
		tmp = tmp->next;
	}
}

void	sort_export(t_list **list)
{
	int swapped = 1;
	t_list *ptr1;
	t_list *lptr = NULL;
	
	while (swapped)
	{
		swapped = 0;
		ptr1 = *list;
		while (ptr1->next != lptr)
		{
			if (ft_strncmp(ptr1->content, ptr1->next->content, ft_strlen(ptr1->content)) > 0)
			{
				char *tmp = ptr1->content;
				ptr1->content = ptr1->next->content;
				ptr1->next->content = tmp;
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

int find_equal(char *s)
{
	int i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

int alloc_quote(char **s)
{
	int len;
	char *ret;
	int i;
	int j;
	int flag;

	len = ft_strlen(*s);
	if ((ret = (char *)malloc(sizeof(char) * (len + 2) + 1)) == NULL)
		return -1;
	i = 0;
	j = 0;
	flag = 0;
	while ((*s)[i])
	{
		ret[j] = (*s)[i];
		if ((*s)[i] == '=' && flag == 0)
		{
			j++;
			ret[j] = '\"';
			flag = 1;
		}
		i++;
		j++;
	}
	ret[j] = '\"';
	ret[j + 1] = 0;
	*s = ret;
	return 1;
}

int add_quot(t_list **list)
{
	t_list *tmp;
	static int flag = 0;

	tmp = *list;
	while (tmp && flag == 0)
	{
		if (find_equal((char *)tmp->content))
			if (alloc_quote((char **)&tmp->content) == -1)
				return -1;
		tmp = tmp->next;
	}
	flag = 1;
	return 1;
}

void	alloc_update(char *cwd, t_list *node)
{
	int len;
	char *ret;
	int i;
	int j;
	char *pwd;

	len = ft_strlen(cwd);
	if ((ret = (char *)malloc(sizeof(char) * (len + ft_strlen(PWD) + 2) + 1)) == NULL)
	{
		printf("malloc fucked up!! \n");
		exit(0);
	}
	i = 0;
	j = 0;
	pwd = PWD;
	while (ret[j])
		ret[j] = pwd[j++];
	ret[j] = '\"';
	j++;
	while (cwd[i])
	{
		ret[j] = cwd[i];
		i++;
		j++;
	}
	ret[j] = '\"';
	ret[j + 1] = 0;
	node->content = ret;
	
	printf("%p %s\n", node->content, node->content);
}

int update_exp_cwd(t_list **list)
{
	t_list *tmp;
	char *cur_cwd;
	char buf[100];

	tmp = *list;
	cur_cwd = getcwd(buf, sizeof(buf));
	while (tmp)
	{
		/* 큰 따옴표를 추가해버려서 그 다음부터는 "PWD= 가 돼버려서 조건문에 안 들어온다. */
		if (!ft_strncmp((char *)tmp->content, PWD, ft_strlen(PWD)))
		{
			alloc_update(cur_cwd, tmp);
			printf("%p %s\n", tmp->content, tmp->content);
		}
		// printf("hoolA!!! %s\n", tmp->content);
		tmp = tmp->next;
	}
}

// export basic
int ft_export(char *line, t_list *list)
{
	int i = 0;

	if (!ft_strncmp(line, "export", ft_strlen("export")))
	{
		update_exp_cwd(&list);
		// sort_export(&list);
		// if (add_quot(&list) == -1)
		// {
		// 	printf("fucked up by malloc\n");
		// 	exit(0);
		// }
		// while (list)
		// {
		// 	write(1, "declare -x ", 11);
		// 	printf("%s\n", (char *)list->content);
		// 	list = list->next;
		// }
	}
}

// env basic
int ft_env(char *line, t_list *list)
{
	if (line[0] == 'e' && line[1] == 'n' && line[2] == 'v')
	{
		update_cwd(&list);
		while (list)
		{
			printf("%s\n", (char *)list->content);
			list = list->next;
		}
	}
}

//pwd 구현 
int pwd(char *line)
{
	char *cwd;
	char buf[100];
	int i;

	i = 0;
	if (line[0] == 'p' && line[1] == 'w' && line[2] == 'd')
	{
		cwd = getcwd(buf, sizeof(buf));
		printf("%s\n", cwd);
		return 1;
	}
	return 0;
}

// cd 명령어 구현. 
int cd(char *line, t_list **env_list, t_list **exp_list)
{
	char buf[100];
	int i;
	int ret;
	struct stat file;
	char *cwd;
	t_list *tmp;
	tmp = *env_list;
	/* export update 하는 부분 구현해야 한다. */

	if (line[0] == 'c' && line[1] == 'd' && ft_isspace(line[2]))
	{
		/* OLDPWD를 업데이트 하기 위해서는 디렉토리를 변경하기 전에 현재 cwd를 넣어준다 */
		cwd = getcwd(buf, sizeof(buf));
		while (tmp)
		{
			if (!ft_strncmp((char *)tmp->content, OLDPWD, ft_strlen(OLDPWD)))
			{
				ft_strlcpy((char *)tmp->content + ft_strlen(OLDPWD), cwd, ft_strlen(cwd) + 1);
			}
			tmp = tmp->next;
		}
		i = 3;
		while (ft_isspace(line[i]))
			i++;
		if ((ret = stat(&line[i], &file)) == -1)
			return -1;
		if (S_ISDIR(file.st_mode))
		{
			if ((ret = chdir(&line[i])) == -1)
				return -1;
			cwd = getcwd(buf, sizeof(buf));
		}
	}
	// else
	// {
	// 	printf("command not found : %s\n", &line[i]);
	// }
	/* 어떻게 하면 space를 기준으로 명령어 토큰을 나눌 수 있을까를 생각해라 */
	return 1;
}

int main(int argc, char *argv[])
{
	/* env linked list 부분 일단 */
	t_list env_head;
	env_head.content = environ[0];
	env_head.next = NULL;
	t_list *env_list = &env_head;

	int i = 1;
	while (environ[i])
	{
		t_list *tmp1 = ft_lstnew(environ[i]);
		ft_lstadd_back(&env_list, tmp1);
		i++;
	}
	/* env --------------------- */

	/* export linked list 부분 일단 */
	t_list exp_head;
	exp_head.content = environ[0];
	exp_head.next = NULL;
	t_list *exp_list = &exp_head;

	i = 1;
	while (environ[i])
	{
		t_list *tmp2 = ft_lstnew(environ[i]);
		ft_lstadd_back(&exp_list, tmp2);
		i++;
	}
	/* export --------------------- */

	char buf[100];
	int ret;
	char *line;
	char **commands;
	i = 0;
	int j = 0;
	
	ret = 0;
	while (1)
	{
		ft_putstr_fd("\033[31mbash\033[0m\033[32m-\033[0m\033[33m3.2\033[0m$ ", 1);
		if ((ret = get_next_line(0, &line)) < 0)
		{
			printf("gnl error\n");
			free(line);
			exit(0);
		}
		while (ft_isspace(line[i]))
			i++;
		cd(&line[i], &env_list, &exp_list);
		pwd(&line[i]);
		ft_env(&line[i], env_list);
		ft_export(&line[i], exp_list);
		free(line);
	}

	while (1)
	{
		;
	}
	return 0;
}

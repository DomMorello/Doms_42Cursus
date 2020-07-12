#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *s)
{
    int len = 0;

    while (s[len])
        len++;
    return (len);
}

void ft_bzero(char *s, int len)
{
    int i = 0;

    while (i <= len)
    {
        s[i] = 0;
        i++;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        write(1, "\n", 1);
        return 0;
    }
    int len1 = ft_strlen(argv[1]);
    int len2 = ft_strlen(argv[2]);
    int len = 0;
    if (len1 >= len2)
        len = len1;
    else
        len = len2;
    
    char save[len];
    ft_bzero(save, len);
    int i = 0;
    int j = 0;
    int s_idx = 0;
    
    while (argv[1][i])
    {
        j = 0;
        while (argv[2][j])
        {
            if (argv[1][i] == argv[2][j])
            {
                save[s_idx] = argv[1][i];
                s_idx++;
                break ;
            }
            j++;
        }
        i++;
    }
    printf("save: %s\n", save);
    len = ft_strlen(save);
    char ret[len];
    ft_bzero(ret, len);
    int r_idx = 0;
    int flag = 0;
    i = 0;

    // fuck it
    return 0;
}
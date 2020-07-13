#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *s)
{
    int len = 0;
    
    while (s[len])
        len++;
    return (len);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        write(1, "\n", 1);
        return 0;
    }
    int len = 0;
    int len1 = ft_strlen(argv[1]);
    int len2 = ft_strlen(argv[2]);
    if (len1 >= len2)
        len = len1;
    else
        len = len2;
    printf("len:%d\n", len);
    int i = 0;
    char save[len];

    while (i < len)
    {
        save[i] = 0;
        i++;
    }
    
    
    return 0;
}

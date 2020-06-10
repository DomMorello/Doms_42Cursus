#include "./main.h"
#include "./gnl/get_next_line.h"

int     error(char *str)
{
    write(1, str, ft_strlen(str));
    return (ERROR);
}

int     parse_info(char const *argv)
{
    int fd;
    char *line;

    if ((fd = open(argv, O_RDONLY)) == -1)
        return (error("Error\ncannot open the file"));
    while (get_next_line(fd, &line))
    {
        check_tex(line);        
    }
}

char     *ft_strfromend(char *str, int size)
{
    int len;
    int j;
    char *copy;

    if ((copy = (char *)malloc(sizeof(char) * size + 1)) == NULL)
        return (NULL);
    len = ft_strlen(str);
    j = 0;
    while (size)
    {
        copy[j++] = str[len - size];
        size--;
    }
    copy[j] = '\0';
    return (copy);
}

int     check_extension(char const *argv)
{
    char *extension;

    if ((extension = ft_strfromend((char *)argv, 4)) == NULL)
        return (FALSE);
    if (!ft_strncmp(extension, ".cub", 5))
        return (TRUE);
    else
        return (FALSE);
}

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        if (check_extension(argv[1]) == FALSE || parse_info(argv[1]) == ERROR)
            return (ERROR);
    }
    else if (argc == 3)
        /* bmp */
    
    return 0;
}


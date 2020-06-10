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

    }
}

int main(int argc, char const *argv[])
{
    if (argc == 2)
    {
        if (check_argv(argv[1]) == ERROR || parse_info(argv[1]) == ERROR)
            return (ERROR);
    }
    else if (argc == 3)
        /* bmp */
    
    return 0;
}


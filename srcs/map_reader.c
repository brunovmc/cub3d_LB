#include "cub3d.h"

int     map_reader(int argc, char **argv)
{
    check_args(argc, argv);
    split_file(read_file(argv[1]));
    check_header();
    check_map();   
}

char    *check_args(argc, argv)
{
    if (argc == 1 )
        return (ft_error(MISSING_ARGUMENT));
    else if (argc > 3)
        return (ft_error(TOO_MANY_ARGUMENTS));
    
}

static char     *read_file(const char *argv)
{
    int fd;
    int ret;
    char *line;
    static char *file;
    
    fd = open(argv, O_RDONLY);
    ret = get_next_line(fd, &line);
    file = ft_strjoin(file, line);
    while (line)
    {
        file = ft_strjoin(file, line);
        free(line);
        if (ret <= 0)
            break;
        ret = get_next_line(fd, &line);
    }
    close(fd);
    return (file);
}

void    split_file(char * file)
{

}

char     *check_header()
{

}

char     *check_map()
{

}

char     *ft_error(int error_num)
{
    return(ft_putstr(g_errors[error_num]));
}
#include "cub3d.h"

int     map_reader(int argc, char **argv)
{
    // pensei em fazer um if aqui, se qualquer uma dessa der erro map reader retorna erro e fecha la na main
    check_args(argc, argv);
    read_file(argv[1]);
    check_map();   
}

int    check_args(argc, argv)
{
    if (argc == 1 )
        return (ft_error(MISSING_ARGUMENT));
    else if (argc > 3)
        return (ft_error(TOO_MANY_ARGUMENTS));
    // else if (argv[2] != "--save")
    //     return (ft_error(SAVE_TYPO));
    else
        return (TRUE);
    
    
}

static char     *read_file(const char *argv)
{
    int fd;
    int ret;
    char *line;
    t_map  map;

    fd = open(argv, O_RDONLY);
    ret = get_next_line(fd, &line);
    while (line)
    {
        if (check_header())
        {
            //max_line_len
            map.map[i][0] = ft_strjoin(map.map[i], line);
            i++;
        } //chegou no mapa comeca a guardar
            
        free(line);
        if (ret <= 0)
            break;
        ret = get_next_line(fd, &line);
    }
    close(fd);
    return (); //retorna mapa e joga map no vars na main?
}

int     check_header(char * line) //enquanto os valores nao forem passados retorna falso
{
    if (ft_is_strnstr(line, "R ", 2)) //lembrar de checar se valor de r ja existe
        return(check_resolution(line));
    else if (ft_is_strnstr(line, "NO ", 3))
        check_texture(line, "NO");
    else if (ft_is_strnstr(line, "SO ", 3))
        check_texture(line, "SO");
    else if (ft_is_strnstr(line, "WE ", 3))
        check_texture(line, "WE");
    else if (ft_is_strnstr(line, "EA ", 3))
        check_texture(line, "EA");
    else if (ft_is_strnstr(line, "S ", 2))
        check_sprite(line);
    else if (ft_is_strnstr(line, "C ", 2))
        check_rgb(line, 'C');
    else if (ft_is_strnstr(line, "F ", 2))
        check_rgb(line, 'F');
    else if (ft_is_strnstr(line, "\n", 1))
        return (FALSE);
    else if (header_values())
        return (TRUE);
    else
        return (FALSE);
}

int     get_header_values(char *line)
{

}

int     check_map()
{
    check_map_character();
    
}

int check_map_character(char c)
{
    if (c != 0 || c != 1 || c != 2 || c != 'N' ||
     c != 'S' || c != 'E' || c != 'W')
        return (ft_error(WRONG_CHARACTER));
    return (TRUE);
}

int     normalize_map()
{

}

int     ft_error(int error_num)
{
    ft_putstr(g_errors[error_num]);
    exit(0);
}

int     ft_is_strnstr(char * haystack, char *needle, int len)
{
    size_t i;
    size_t j;
    size_t n_len;

    i = 0;
    n_len = ft_strlen(needle);
    if (needle[i] == '\0')
        return (FALSE);
    while (haystack[i] && i < len)
    {
        j = 0;
        while (haystack[i + j] == needle[j] && i + j < len)
        {
            if (j = n_len -1)
                return (TRUE);
            j++;
        }
        i++;
    }
    return (FALSE);
}

int     ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
        i++;
    return (i);
}
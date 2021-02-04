#include "cub3d.h"

int     map_reader(int argc, char **argv)
{
    // pensei em fazer um if aqui, se qualquer uma dessa der erro map reader retorna erro e fecha la na main
    check_args(argc, argv);
    read_file(argv[1]);
    check_header();
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
        if (!check_header()) //verif linha a linha do header
           get_header_values(line); //coloca os valores do header
        else if (check_header()) //chegou no mapa comeca a guardar
            map.map = ft_strjoin(map.map, line);
        free(line);
        if (ret <= 0)
            break;
        ret = get_next_line(fd, &line);
    }
    close(fd);
    return (); //retorna mapa e joga map no vars na main?
}

int     check_header() //enquanto os valores nao forem passados retorna falso
{
    //resolucao
    //texturas
    //sprites
    //teto
    //chao
}

int     get_header_values(char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[0] != ) //R N S W E C F
            return (ft_error(INVALID_FILE));
        if (line[1] != ) //O E A ' '
            return (ft_error(INVALID_FILE));
        if (line[0] == '\n')
            break;
        i++;
    }
    return (TRUE);
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
    return (-1);
}
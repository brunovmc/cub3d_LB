#include "cub3d.h"

int     map_reader(int argc, char **argv, t_vars *vars)
{
    // pensei em fazer um if aqui, se qualquer uma dessa der erro map reader retorna erro e fecha la na main
    check_args(argc, argv);
    read_file(argv[1], vars);
    //printf("%s\n", argv[1]);
    //check_map(); 
    return (TRUE);  
}

int    check_args(int argc, char **argv)
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

int     read_file(const char *argv, t_vars *vars)
{
    int     fd;
    int     ret;
    char    *line;
    int     i;
    //t_map  map;  acho melhor tirar t map daqui
    fd = open(argv, O_RDONLY);
    ret = get_next_line(fd, &line);
    i = 0;
    while (line)
    {
        printf("%s\n", line);
        if (check_header(line, vars))
        {
            //max_line_len
            //vars->map->map[i][0] = ft_strjoin(vars->map->map[i], line);
            //i++;
        }
        free(line);
        
        if (ret <= 0)
            break;
        ret = get_next_line(fd, &line);
    }
    close(fd);
    return (TRUE); 
}

int     check_header(char *line, t_vars *vars) //enquanto os valores nao forem passados retorna falso
{
    //if (header_values(vars))
        //return (TRUE);
    if (ft_is_strnstr(line, "R ", 2)) //lembrar de checar se valor de r ja existe
        return(check_resolution(line, vars));
    // else if (ft_is_strnstr(line, "NO ", 3))
    //     check_texture(line, "NO", vars);
    // else if (ft_is_strnstr(line, "SO ", 3))
    //     check_texture(line, "SO", vars);
    // else if (ft_is_strnstr(line, "WE ", 3))
    //     check_texture(line, "WE", vars);
    // else if (ft_is_strnstr(line, "EA ", 3))
    //     check_texture(line, "EA", vars);
    // else if (ft_is_strnstr(line, "S ", 2))
    //     check_sprite(line, vars);
    // else if (ft_is_strnstr(line, "C ", 2))
    //     check_rgb(line, 'C', vars);
    // else if (ft_is_strnstr(line, "F ", 2))
    //     check_rgb(line, 'F', vars);
    else if (ft_is_strnstr(line, "\n", 1))
        return (FALSE);
    else
        return (FALSE);
}

int     header_values(t_vars *vars)
{
    if (vars->width == 0 && vars->height == 0)
        return (FALSE); 
    return (TRUE);
}

int     check_resolution(char *line, t_vars *vars)
{
    int i;
    int width;
    int height;

    width = 0;
    height = 0;
    vars->width = 0;
    vars->height = 0;
    i = 2; //pra pular o "R "
    while (ft_isnum(line[i]) || line[i] == ' ')
    { 
        if (ft_isnum(line[i]) && vars->width == 0)
            width = (width * 10) + (line[i] - '0');
        else if (ft_isnum(line[i]) && vars->height == 0)
            height = (height * 10) + (line[i] - '0');
        else if (line[i] == ' ' && width > 0)
            vars->width = width;
        i++;
    }
    vars->height = height;
    printf("vars->w = %i \n", vars->width);
    printf("vars->h = %i \n", vars->height);
    return ((vars->width > 0 && vars->height > 0) 
        ? TRUE : ft_error(WRONG_RESOLUTION));
}

// int     check_texture(char *line, char *side, t_vars *vars)
// {

// }

// int     check_map()
// {
//     check_map_character();
    
// }

// int check_map_character(char c)
// {
//     if (c != 0 || c != 1 || c != 2 || c != 'N' ||
//      c != 'S' || c != 'E' || c != 'W')
//         return (ft_error(WRONG_CHARACTER));
//     return (TRUE);
// }

// int     normalize_map()
// {

// }

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
            if (j == (n_len -1))
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

int    ft_putchar(char c)
{
    write(1, &c, 1);
    return (1);
}

int ft_isnum(int c)
{
    if (c >= 48 && c <= 57)
        return (1);
    return (0);
}

void    ft_putstr(char *str)
{
    unsigned int i;

    i = 0;
    if  (str != 0)
    {
        while (str[i])
        {
            ft_putchar(str[i]);
            i++;
        }
    }
}

int get_next_line(int fd, char **line)
{
    static char *s_line;
    char *l_buffer;
    register int result;

    if (!line || fd < 0 || BUFFER_SIZE < 1)
        return (-1);
    result = 1;
    *line = NULL;
    l_buffer = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
    if (!s_line)
        s_line = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
    while (newline(s_line) == -1 && result >= 1 && result <= BUFFER_SIZE)
    {
        result = read(fd, l_buffer, BUFFER_SIZE);
        if (result >= 1 && result <= BUFFER_SIZE && s_line)
            s_line = ft_strjoin(s_line, l_buffer);
        ft_bzero(l_buffer);
    }
    if (result >= 0 && result <= BUFFER_SIZE)
        s_line = cleanline(line, s_line, newline(s_line));
    free(l_buffer);
    if (result >= 1 && result <= BUFFER_SIZE)
        return (1);
    return (result == 0 ? 0 : -1);
}

/*
** Responsável por concatenar duas strings
*/

char *ft_strjoin(char *s1, char *s2)
{
    char *str;
    register int i;
    register int j;

    i = ft_strlen(s1);
    j = ft_strlen(s2);
    str = (char *)ft_calloc(i + j + 1, sizeof(char));
    i = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    j = 0;
    while (s2[j])
    {
        str[i + j] = s2[j];
        j++;
    }
    free(s1);
    return (str);
}

/*
** A função recebe como parâmetro **line e *s_line, que contem uma string
** com uma quebra de linha em alguma posição. *cleanline é responsável por
** copiar os caracteres até o \n para a *line e retornar uma string com
** os caracteres seguintes para a próxima interação.
*/

char *cleanline(char **line, char *s_line, int j)
{
    char *l_temp;

    if (j >= 0)
    {
        s_line[j] = '\0';
        *line = (char *)ft_calloc(ft_strlen(s_line) + 1, sizeof(char));
        l_temp = (char *)ft_calloc(ft_strlen(&s_line[j + 1]) + 1, sizeof(char));
        ft_strlcpy(*line, s_line, ft_strlen(s_line) + 1);
        ft_strlcpy(l_temp, &s_line[j + 1], ft_strlen(&s_line[j + 1]) + 1);
        free(s_line);
        s_line = NULL;
        return (l_temp);
    }
    *line = (char *)ft_calloc(ft_strlen(s_line) + 1, sizeof(char));
    ft_strlcpy(*line, s_line, ft_strlen(s_line) + 1);
    free(s_line);
    s_line = NULL;
    return (s_line);
}

/*
** Verifica se existe uma quebra de linha na string passada como
** parâmetro, retornando o índice caso o encontre. Retorna -1 em caso contrário.
*/

int newline(char *s_line)
{
    int i;

    i = 0;
    if (!s_line)
        return (-1);
    while (s_line[i])
    {
        if (s_line[i] == '\n')
            return (i);
        i++;
    }
    return (-1);
}

void ft_bzero(char *str)
{
    int i;

    i = 0;
    if (str)
    {
        while (i < BUFFER_SIZE && i < 1000000)
        {
            str[i] = '\0';
            i++;
        }
    }
}

char *ft_calloc(size_t count, size_t size)
{
    char *str;
    size_t i;

    if (count > 1000000)
        count = 1000000;
    str = (char *)malloc(count * size);
    i = 0;
    if (str)
    {
        while (i < count)
        {
            str[i] = '\0';
            i++;
        }
    }
    return (str);
}

size_t ft_strlcpy(char *dst, char *src, size_t dstsize)
{
    size_t i;

    if (src == 0)
        return (0);
    if (dstsize > 0)
    {
        i = 0;
        while (src[i] != '\0' && i < (dstsize - 1))
        {
            dst[i] = src[i];
            i++;
        }
        dst[i] = '\0';
    }
    return (ft_strlen(src));
}
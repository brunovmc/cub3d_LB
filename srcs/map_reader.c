#include "cub3d.h"

int     map_reader(int argc, char **argv, t_vars *vars)
{
    // pensei em fazer um if aqui, se qualquer uma dessa der erro map reader retorna erro e fecha la na main
    check_args(argc, argv);
    read_file(argv[1], vars);
    normalize_map(vars->map->rows, vars->map->cols, vars);
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
    // else if (ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) != 0)
    //      return (ft_error(SAVE_TYPO));
    else
        return (TRUE);
    
    
}

int     read_file(const char *argv, t_vars *vars)
{
    int     fd;
    int     ret;
    char    *line;
    int     i;

    fd = open(argv, O_RDONLY);
    ret = get_next_line(fd, &line);
    i = 0;
    while (line[i])
    {
        if (check_header(line, vars) && line[0])
        {
            if(ft_strchr("102 NSWE", line[i]))
            {
                //get_player
                if (ft_strchr("NSWE", line[i]))
                {
                    vars->player->x = /*ate a posicao de line[i]*/;
                    vars->player->y = vars->map->rows;
                }
                else if (vars->player->x != 0 || vars->player->y != 0)
                    ft_error(/*TOO_MANY_PLAYERS*/);
            }
            else
                ft_error(/*WRONG_MAP_CHAR*/);
            if (ft_strlen(line) > vars->map->cols)
                vars->map->cols = ft_strlen(line);
            allocate_map(line, vars);
            vars->map->rows++;
        }
        free(line);
        if (ret <= 0)
            break;
        ret = get_next_line(fd, &line);
        i++;
    }
    
    printf("rows = %i\n", vars->map->rows);
    printf("cols = %i\n", vars->map->cols);
    close(fd);
    return (TRUE); 
}

int allocate_map(char *line, t_vars *vars)
{
    int i;

    i = 0;

    if (!vars->map->rows)
    {
        if (ft_strlen(line))
        {
            vars->map->map = (char **)ft_calloc(sizeof(char *), 1);
            vars->map->map[0] = ft_strdup(line);
        }
    }
    else
        vars->map->map = matrix_buffer(vars->map->map, ft_strdup(line), vars->map->rows);
    return (0);
}

char **matrix_buffer(char **map, char *line, int cols)
{
    char **tmp;
    int i;

    i = 0;
    tmp = (char **)ft_calloc(sizeof(char *), (cols + 1));
    while (i < cols)
    {
        tmp[i] = map[i];
        i++;
    }
    tmp[i] = line;
    free(map);
    return (tmp);
}

int     normalize_map(int rows, int cols, t_vars *vars)
{
    //char **map;
    int i;
    int j;
    int len;

    i = 0;
    vars->map->grid = (char **)ft_calloc(sizeof(char *), rows + 1);
    while (i < (rows - 1))
    {
        j = 0;
        vars->map->grid[i] = (char *)ft_calloc(sizeof(char), cols + 1);
        len = ft_strlen(vars->map->map[i]);
        while (j < cols)
        {
            if (j < len)
                vars->map->grid[i][j] = vars->map->map[i][j];
            else
                vars->map->grid[i][j] = ' ';
            j++;
        }
        vars->map->grid[i][j] = '\0';
        i++;
    }
    vars->map->grid[i] = NULL;
    clear_pointer(vars->map->map);
    return (0);
}

int clear_pointer(char **p)
{
    int i;

    i = 0;
    while (p[i])
    {
        free(p[i]);
        i++;
    }
    free(p);
    return (0);
}

int     check_header(char *line, t_vars *vars)
{
    //printf("line[0]: %c\n", line[0]);
    if (ft_strchr(line, 'R') == &line[0])
        return(check_resolution(line, vars));
    else if (ft_strncmp(line, "NO ", 3) == 0)
        return(check_texture(line, 'N', vars));
    else if (ft_strncmp(line, "SO ", 3) == 0)
        return(check_texture(line, 'S', vars));
    else if (ft_strncmp(line, "WE ", 3) == 0)
        return(check_texture(line, 'W', vars));
    else if (ft_strncmp(line, "EA ", 3) == 0)
        return(check_texture(line, 'E', vars));
    else if (ft_strncmp(line, "S ", 2) == 0)
        return(check_texture(line, 'X', vars));
    else if (ft_strncmp(line, "C ", 2) == 0)
        return (check_rgb(line, 'C', vars));
    else if (ft_strncmp(line, "F ", 2) == 0)
        return (check_rgb(line, 'F', vars));
    return (TRUE);
}

unsigned long int   rgb_hex(int r, int g, int b)
{
    return (((r & 0xff) << 16) + ((g & 0xff) << 8) + (b & 0xff)); 
}

int     check_rgb(char *line, char c, t_vars *vars)
{
    char **nums;
    char **rgb;


    nums = ft_split(line, ' ');
    rgb = ft_split(nums[1], ',');

    printf("num[0]: %s\n", nums[0]);
    printf("num[1]: %s\n", nums[1]);
    printf("rgb[0]: %s\n", rgb[0]);
    printf("rgb[1]: %s\n", rgb[1]);
    printf("rgb[2]: %s\n", rgb[2]);
    if (nums[2] || rgb[3])
        ft_error(TOO_MANY_RGB_ARGS);
    if (!(aredigits(rgb[0])) || !(aredigits(rgb[1])) || !(aredigits(rgb[2]))
        || ft_atoi(rgb[0]) < 0 || ft_atoi(rgb[0]) > 255 || ft_atoi(rgb[1]) < 0
        || ft_atoi(rgb[1]) > 255 || ft_atoi(rgb[2]) < 0 || ft_atoi(rgb[2]) > 255)
        ft_error(NOT_RGB_NUMBER);
    if (c == 'C')
        vars->map->ceiling = rgb_hex(ft_atoi(rgb[0]), ft_atoi(rgb[1]),ft_atoi(rgb[2]));
    if (c == 'F')
        vars->map->floor = rgb_hex(ft_atoi(rgb[0]), ft_atoi(rgb[1]),ft_atoi(rgb[2]));
    printf("ceiling: %x\n", vars->map->ceiling);
    printf("floor  : %x\n", vars->map->floor);
    return (0);
}

int     check_texture(char *line, char c, t_vars *vars)
{
    char    **path;
    char    **ext;

    path = ft_split(line, ' ');
    ext = ft_split(path[1], '.');
    if (ft_strncmp(ext[1], "xpm", ft_strlen(ext[1])) != 0)
        ft_error(NOT_XPM);
    if (path[2])
        ft_error(TOO_MANY_TXT_ARGS);
    if (c == 'N')
        vars->map->no = path[1];
    else if (c == 'S')
        vars->map->so = path[1];
    else if (c == 'W')
        vars->map->we = path[1];
    else if (c == 'E')
        vars->map->ea = path[1];
    else if (c == 'X')
        vars->map->s = path[1];
    
    printf("NO: %s\n", vars->map->no);
    printf("SO: %s\n", vars->map->so);
    printf("WE: %s\n", vars->map->we);
    printf("EA: %s\n", vars->map->ea);
    printf("S: %s\n", vars->map->s);
    return (0);
}


int     aredigits(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (!(ft_isdigit(str[i])))
            return (FALSE);
        i++;
    }
    return (TRUE);
}

int     check_resolution(char *line, t_vars *vars)
{
    char    **resolution;
    int     i;

    resolution = ft_split(line, ' ');
    if (ft_strncmp(resolution[0], "R", ft_strlen(resolution[0])) != 0)
        ft_error(WRONG_RESOLUTION);
    if (resolution[3])
        ft_error(WRONG_RESOLUTION);
    if (!aredigits(resolution[1]) || !aredigits(resolution[2]))
        ft_error(WRONG_RESOLUTION);
    vars->width = ft_atoi(resolution[1]);
    vars->height = ft_atoi(resolution[2]);
    printf("witdh: %i\n", vars->width);
    printf("height: %i\n", vars->height);
    return (0);
}

/*
int     check_header(char *line, t_vars *vars) //enquanto os valores nao forem passados retorna falso
{
    // if (header_values(vars))
    //     return (header_values(vars));
    if (ft_is_strnstr(line, "R ", 2)) //lembrar de checar se valor de r ja existe
        return(check_resolution(line, vars));
    else if (ft_is_strnstr(line, "NO ", 3))
        return(check_texture(line, 'N', vars));
    else if (ft_is_strnstr(line, "SO ", 3))
        return(check_texture(line, 'S', vars));
    else if (ft_is_strnstr(line, "WE ", 3))
        return(check_texture(line, 'W', vars));
    else if (ft_is_strnstr(line, "EA ", 3))
        return(check_texture(line, 'E', vars));
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
    while (ft_isdigit(line[i]) || line[i] == ' ')
    { 
        if (ft_isdigit(line[i]) && vars->width == 0)
            width = (width * 10) + (line[i] - '0');
        else if (ft_isdigit(line[i]) && vars->height == 0)
            height = (height * 10) + (line[i] - '0');
        else if (line[i] == ' ' && width > 0)
            vars->width = width;
        i++;
    }
    vars->height = height;
    printf("vars->w = %i \n", vars->width);
    printf("vars->h = %i \n", vars->height);
    return ((vars->width > 0 && vars->height > 0) 
        ? FALSE : ft_error(WRONG_RESOLUTION));
}

int     check_texture(char *line, char side, t_vars *vars)
{
    int i;
    int j;
    char *str;

    str = ft_calloc(50, sizeof(char));
    i = 2; //pra pular o "XX "
    while (line[i] == ' ')
        i++;
    j = 0;
    while (line[i])
    {
        str[j] = line[i];
        j++;
        i++;
    }
    if (side == 'N')
    {
        vars->map->no = ft_calloc(50, sizeof(char));
        ft_strlcpy(vars->map->no, str, ft_strlen(str) + 1);
    } 
    else if (side == 'S')
    {
        vars->map->so = ft_calloc(50, sizeof(char));
        ft_strlcpy(vars->map->so, str, ft_strlen(str) + 1);
    }
    else if (side == 'W')
    {
        vars->map->we = ft_calloc(50, sizeof(char));
        ft_strlcpy(vars->map->we, str, ft_strlen(str) + 1);
    }
    else if (side == 'E')
    {
        vars->map->ea = ft_calloc(50, sizeof(char));
        ft_strlcpy(vars->map->ea, str, ft_strlen(str) + 1);
    }
    printf("str = %s \n", str);
    printf("vars->map->no = %s \n", vars->map->no);
    printf("vars->map->so = %s \n", vars->map->so);
    printf("vars->map->we = %s \n", vars->map->we);
    printf("vars->map->ea = %s \n", vars->map->ea);
    free(str);
    // if (vars->map->no != '\0' && vars->map->so != '\0' && 
    //     vars->map->we != '\0' && vars->map->ea != '\0')
    //     return (TRUE);
    return (FALSE);
}

int check_texture2(char *line, char side, t_vars *vars)
{
    return (0);
}

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

*/

    int ft_error(int error_num)
{
    ft_putstr_fd("ERROR:\n", 1);
    ft_putstr_fd(g_errors[error_num], 1);
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

void	ft_bzero_gnl(char *str)
{
	int	i;

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
        ft_bzero_gnl(l_buffer);
    }
    if (result >= 0 && result <= BUFFER_SIZE)
        s_line = cleanline(line, s_line, newline(s_line));
    free(l_buffer);
    if (result >= 1 && result <= BUFFER_SIZE)
        return (1);
    return (result == 0 ? 0 : -1);
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

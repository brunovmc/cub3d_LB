#include "cub3d.h"

int     map_reader(int argc, char **argv, t_vars *vars)
{
    // pensei em fazer um if aqui, se qualquer uma dessa der erro map reader retorna erro e fecha la na main
    check_args(argc, argv);
    init_header(vars);
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
    // else if (argv[2] != "--save")
    //     return (ft_error(SAVE_TYPO));
    else
        return (TRUE);
    
    
}

void    init_player(t_vars *vars, char direction, int x, int y)
{
    vars->player->x = (y * TILE_SIZE + TILE_SIZE/2);// * MINIMAP_SCALE_FACTOR;
    vars->player->y = (x * TILE_SIZE + TILE_SIZE/2);// * MINIMAP_SCALE_FACTOR;
    if (direction == 'N')
        vars->player->rotation_angle = NORTH;
    else if (direction == 'S')
        vars->player->rotation_angle = SOUTH;
    else if (direction == 'E')
        vars->player->rotation_angle = EAST;
    else if (direction == 'W')
        vars->player->rotation_angle = WEST;
}


int     check_character_map(t_vars *vars, char *line)
{
    int i;
    int quant;

    i = 0;
    quant = 0; //quant players
    while (line[i] && ft_strchr(" 012NSWE\n", line[i]))
    {
        if (line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'W')
        {
            init_player(vars, line[i], vars->map->rows, i);
            quant++;
        }
        if (line[i] == '2')
            vars->map->quantsprites++;
        i++;
    }
    if (i != ft_strlen(line))
        return (ft_error(WRONG_CHARACTER));
    return (quant);
}


int     read_file(const char *argv, t_vars *vars)
{
    int     fd;
    int     ret;
    char    *line;
    int     quantplayer;

    fd = open(argv, O_RDONLY);
    ret = get_next_line(fd, &line);
    quantplayer = 0;
    while (line)
    {
        if (line[0] && check_header(line, vars))
        {
            quantplayer += check_character_map(vars, line);
            if (ft_strlen(line) > vars->map->cols)
                vars->map->cols = ft_strlen(line);
            allocate_map(line, vars);
            vars->map->rows++;
        }
        free(line);
        if (ret <= 0)
            break;
        ret = get_next_line(fd, &line);
    }
    printf("quantplayer: %i\n", quantplayer);
    printf("quantsprite: %i\n", vars->map->quantsprites);
    if (quantplayer != 1)
        ft_error(WRONG_PLAYER);
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

int		is_char_allowed(char c)
{
	if (!c)
		return (FALSE);
	if (ft_strchr("012NSEW", c))
		return (TRUE);
	return (FALSE);
}

int		check_sides_map(t_vars *vars, int row, int col)
{
	if (((row == 0 || row == (vars->map->rows - 1)) || (col == 0 ||
	col == vars->map->cols - 1)) &&
	(!(ft_strchr("1 ", vars->map->grid[row][col]))))
        ft_error(NOT_SURROUND_1);
	else if ((row > 0 && row < vars->map->rows - 1) &&
	(col > 0 && col < vars->map->cols - 1) &&
	(ft_strchr("02NSWE", vars->map->grid[row][col])) &&
	((!(is_char_allowed(vars->map->grid[row - 1][col]))) ||
	(!(is_char_allowed(vars->map->grid[row + 1][col]))) ||
	(!(is_char_allowed(vars->map->grid[row][col + 1]))) ||
	(!(is_char_allowed(vars->map->grid[row][col - 1]))) ||
	(!(is_char_allowed(vars->map->grid[row - 1][col - 1]))) ||
	(!(is_char_allowed(vars->map->grid[row + 1][col - 1]))) ||
	(!(is_char_allowed(vars->map->grid[row - 1][col + 1]))) ||
	(!(is_char_allowed(vars->map->grid[row + 1][col + 1])))))
    {
        printf("row: %d - col: %d\n", row, col);
		ft_error(INVALID_MAP);
    }
    //else
    //    printf("AAAAAAA\n");
    
    return(1);
}

int     check_map(t_vars *vars)
{
    int i;
    int j;

    i = 0;
    //printf("6\n");
    while (i < vars->map->rows)
    {
        //printf("%i\n", i);
        j = 0;
        while (j < vars->map->cols)
        {
            //printf("%i", j);
            //printf("%c",vars->map->map[i][j]);
            check_sides_map(vars, i, j);
            j++;
        }
        i++;
    }
    //printf("rows: %d\ncols: %d\n", vars->map->rows, vars->map->cols);
    return (1);
}

int     normalize_map(int rows, int cols, t_vars *vars)
{
    //char **map;
    int i;
    int j;
    int len;

    i = 0;
    vars->map->grid = (char **)ft_calloc(sizeof(char *), rows + 1);
    while (i < (rows)) //aqui tinha um rows - 1
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
        printf("%s\n", vars->map->grid[i]);
        i++;
    }
    vars->map->grid[i] = NULL;
    clear_pointer(vars->map->map);
    return (check_map(vars));
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
    else if (header_full(vars))
        return (TRUE);
    else
        ft_error(INVALID_HEADER);
    return (FALSE);
}

void    init_header(t_vars *vars)
{
    vars->width = 0;
    vars->height = 0;
    vars->map->no = NULL;
    vars->map->so = NULL;
    vars->map->we = NULL;
    vars->map->ea = NULL;
    vars->map->s = NULL;
    vars->map->ceiling = -1;
    vars->map->floor = -1;
    vars->map->quantsprites = 0;
    mlx_get_screen_size(vars->mlx, &vars->max_width, &vars->max_height);
}

int     header_full(t_vars *vars)
{
    if (vars->width != 0 && vars->height != 0 && vars->map->ceiling != -1
     && vars->map->floor !=-1 && vars->map->no
      && vars->map->so && vars->map->we
       && vars->map->ea && vars->map->s)
        return (TRUE);
    return (FALSE);
}

unsigned int rgb_hex(int r, int g, int b)
{
    return (0 << 24 | r << 16 | g << 8 | b); 
}

int     check_rgb(char *line, char c, t_vars *vars)
{
    char **nums;
    char **rgb;

    if (line[ft_strlen(line) -1] == ',')
        ft_error(WRONG_RGB);
    if (vars->map->ceiling != -1 && vars->map->floor != -1)
        return (ft_error(ALREADY_ASSIGNED));
    nums = ft_split(line, ' ');
    if (nums[1] == NULL)
        ft_error(WRONG_RGB);
    rgb = ft_split(nums[1], ',');
    if (rgb[1] == NULL || rgb[2] == NULL)
        ft_error(WRONG_RGB);
    printf("num[0]: %s\n", nums[0]);
    printf("num[1]: %s\n", nums[1]);
    printf("rgb[0]: %s\n", rgb[0]);
    printf("rgb[1]: %s\n", rgb[1]);
    printf("rgb[2]: %s\n", rgb[2]);
    printf("rgb[3]: %s\n", rgb[3]);
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
    if (!path[1])
        ft_error(NOT_TEXTURE_FILE);
    if (path[2])
        ft_error(TOO_MANY_TXT_ARGS);
    if (ft_strncmp(ext[1], "xpm", ft_strlen(ext[1])) != 0)
        ft_error(NOT_XPM);
    if (c == 'N' && !vars->map->no)
        vars->map->no = path[1];
    else if (c == 'S' && !vars->map->so)
        vars->map->so = path[1];
    else if (c == 'W' && !vars->map->we)
        vars->map->we = path[1];
    else if (c == 'E' && !vars->map->ea)
        vars->map->ea = path[1];
    else if (c == 'X' && !vars->map->s)
        vars->map->s = path[1];
    else
        ft_error(ALREADY_ASSIGNED);
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

    if (vars->width != 0 && vars->height != 0)
        return (ft_error(ALREADY_ASSIGNED));
    resolution = ft_split(line, ' ');
    if (ft_strncmp(resolution[0], "R", ft_strlen(resolution[0])) != 0)
        ft_error(WRONG_RESOLUTION);
    if (resolution[3])
        ft_error(WRONG_RESOLUTION);
    if (!aredigits(resolution[1]) || !aredigits(resolution[2]))
        ft_error(WRONG_RESOLUTION);
    vars->width = ft_atoi(resolution[1]);
    if (vars->width  > vars->max_width)
        vars->width = vars->max_width;
    vars->height = ft_atoi(resolution[2]);
    if (vars->height > vars->max_height)
        vars->height = vars->max_height;
    printf("witdh: %i\n", vars->width);
    printf("height: %i\n", vars->height);
    return (0);
}

    int ft_error(int error_num)
{
    ft_putstr_fd("ERROR\n", 1);
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

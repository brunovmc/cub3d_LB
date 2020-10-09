#include "cub3d.h"

//const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
  //  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    //{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    //{1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    //{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    //{1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1},
    //{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    //{1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    //{1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
    //{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    //{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
//};

void	*ft_calloc(size_t count, size_t size)
{
	char	*mem;
	size_t	i;
	size_t	len;

	len = count * size;
	mem = malloc(len);
	if (mem == 0)
		return (0);
	i = 0;
	while (len > 0)
	{
		mem[i] = '\0';
		i++;
		len--;
	}
	return (mem);
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char 	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
       *(unsigned int*)dst = color;       
}

void	put_rect(t_data *data, int x, int y, int size_x, int size_y, int color)
{
	int a;
	int b;

	a = 0;
	while (a <= size_x)
	{
		b = 0;
		while (b <= size_y)
		{
			my_pixel_put(data, a + x, b + y, color);
			b++;
		}
		a++;
	}
}

void    renderMap(t_vars *vars, t_data *data)
{
    int i;
    int j;
    int tileX;
    int tileY;
    int tileColor;

	//data = alloc_data(vars);
    
    i = 0;
    while (i < MAP_NUM_ROWS)
    {
        j = 0;
        while (j < MAP_NUM_COLS)
        {
            tileX = j * TILE_SIZE;
            tileY = i * TILE_SIZE;
            tileColor = map[i][j] != 1 ? 0X00FFFFFF : 0X00000000;
            //render_rectangle(vars, tileX, tileY, tileX + TILE_SIZE, tileY + TILE_SIZE, tileColor);
			put_rect(data, tileX, tileY, tileX + TILE_SIZE, tileY + TILE_SIZE, tileColor);
            j++;
        }
        i++;
    }
	//mlx_put_image_to_window(vars->mlx, vars->window, data.img, 0, 0);
}

int	close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->window);
	exit(0);
}

void	put_circle(t_data *data, int a, int b, int size, int color)
{
	int x;
	int y;

	x = 0;
	while (x <= (a + size))
	{
		y = 0;
		while (y <= (b + size) )
		{
			if ((x - a) * (x - a) + (y - b) * (y - b) <= size * size)
				my_pixel_put(data, x, y, color);
			y++;

		}
		x++;
	}
}

void	put_line(t_data *data, t_vars *vars, int x, int y, int size, int color)
{
	double dir;
	int i;
	double new_x;
	double new_y;

	i = 0;
	dir = (vars->player->dir * 3.14)/180;
	while (i < size)
	{
		new_x = (size - i) * cos(dir);
		new_y = (size - i) * sin(dir);
	
		my_pixel_put(data,x + new_x, y + new_y, color);
		i++;
	}
	
}

//void	teste(t_vars *vars, int x, int y, int color)
int		update_frame(t_vars *vars)
{
	t_data data;

	// data.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	// data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	data = alloc_data(vars);

	//renderMap(&vars , &data);
	//my_pixel_put(&data, POSX + x, POSY + y, color);
	//put_rect(&data, vars->pos->x, vars->pos->y, 50, 1, 0x00ff0000);
	//put_circle(&data, vars->pos->x, vars->pos->y, 10, 0x00ff0000);
	put_line(&data, vars, vars->pos->x, vars->pos->y, 100, 0x0ff0000);
	mlx_put_image_to_window(vars->mlx, vars->window, data.img, 0, 0);
	return (0);
}

int		keypressed(int key, t_vars *vars)
{
	int		color;

	if (key == W_KEY)
		vars->pos->y -= 10;
	else if (key == A_KEY)
		vars->pos->x -= 10;
	else if (key == S_KEY)
		vars->pos->y += 10;
	else if (key == D_KEY)
		vars->pos->x += 10;
	else if (key == RIGHT_KEY)
	{
		vars->player->dir += 1.0;
		printf("%f\n", vars->player->dir);
	}
	else if (key == LEFT_KEY)
	{
		vars->player->dir -= 1.0;
		printf("%f\n", vars->player->dir);
	}
	else if (key == ESC)
	 	return (close(vars));

	update_frame(vars);
	return(key);
}

t_data 	alloc_data(t_vars *vars)
{
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));

	data->img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);

	return(*data);
}



int	main(void)
{
	t_vars	vars;
	t_point pos;	
	t_player player;

	player.dir = 0.0;
	vars.player = &player;
	pos.x = POSX;
	vars.pos = &pos;

	

	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "TESTE PRIMEIRO");

	// printf("%i\n", vars.pos->x);
	// printf("%i\n", pos.x);

	//printf("%f\n", vars.player->dir);
	printf("%f\n", player.dir);

	mlx_hook(vars.window, 2, 1L << 0, keypressed, &vars);
	//mlx_loop_hook(vars.mlx, update_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}

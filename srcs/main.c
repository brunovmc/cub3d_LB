#include "cub3d.h"

int	close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->window);
	exit(0);
}

void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char 	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
       *(unsigned int*)dst = color;       
}

void    renderMap()
{
    int i;
    int j;
    int tileX;
    int tileY;
    int tileColor;
	t_data	data;
    
    i = 0;
    while (i < MAP_NUM_ROWS)
    {
        j = 0;
        while (j < MAP_NUM_COLS)
        {
            tileX = j * TILE_SIZE;
            tileY = i * TILE_SIZE;
            tileColor = map[i][j] != 1 ? 0X00FFFFFF : 0X00000000;
			put_rect(&data, tileX, tileY, tileX + TILE_SIZE, tileY + TILE_SIZE, tileColor);
            j++;
        }
        i++;
    }
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
/*
void	teste2(t_data *data, int x, int y, int color)
{
	put_circle(data, x, y, 5, color);
}

void	teste(t_data *data, int x, int y, int color)
{
	teste2(data, x, y, color);
}
*/
int		update_frame(t_vars *vars)
{
	t_data data;

	data.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	//renderMap();
	//put_rect(&data, vars->pos->x, vars->pos->y, 15, 15, 0x0000ff00);
	put_circle(&data, vars->pos->x, vars->pos->y, 5, 0x00ff0000);
	//teste(&data, vars->pos->x + POSX, vars->pos->y + POSY, 0x0000ff00);
	
	mlx_put_image_to_window(vars->mlx, vars->window, data.img, 0, 0);
	return 0;
}

int		keypressed(int key, t_vars *vars)
{
	int		color;
	t_data	data;
	static int		x;
	static int		y;

	if (key == W_KEY)
	{
		//y -= 10;
		vars->pos->y -= 10;
		//printf("%d\n", vars->player->pos->y);
	}
	else if (key == A_KEY)
	{
		//x -= 10;
		vars->pos->x -= 10;
		//printf("%d\n", vars->player->pos->x);
	}
	else if (key == S_KEY)
	{
		//y += 10;
		vars->pos->y += 10;
		//printf("%d\n", vars->player->pos->y);
	}
	else if (key == D_KEY)
	{
		//x += 10;
		vars->pos->x += 10;
		//printf("%d\n", vars->player->pos->x);
	}
	else if (key == ESC)
		return (close(vars));

	//vars->pos->x = x;
	//vars->pos->y = y;
	update_frame(vars);

	return(key);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "TESTE PRIMEIRO");
	renderMap(); ////////////////////////
	mlx_hook(vars.window, 2, 1L<<0, keypressed, &vars);
	//mlx_loop_hook(vars.mlx, update_frame, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
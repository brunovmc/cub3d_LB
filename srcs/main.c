#include "cub3d.h"

int	close(t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->window);
	exit(0);
}

/*
void	sethooks(t_vars *vars)
{
	mlx_hook(vars->window, 2, 0, keypressed, &vars);
}
*/

// porque essa funcao funciona???
void	my_pixel_put(t_data *data, int x, int y, int color)
{
	char 	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
       *(unsigned int*)dst = color;       
}

void	put_rect(t_data *data, int x, int y, int size_x, int size_y, int color)
{
	int init_x;

	init_x = x;
	while (y <= size_y)
	{
		x = init_x;
		while (x <= size_x)
		{
			my_pixel_put(data, x, y, color);
			x++;
		}
		y++;
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

void    renderMap(t_data data)
{
    int i;
    int j;
    int tileX;
	int tileY;
	int tileColor;

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

int		keypressed(int key, t_vars *vars)
{
	if (key == W_KEY)
	{
		vars->pos->y -= 10;
		//vars->player->pos->y -= 10;
		//printf("%d\n", vars->player->pos->y);
	}
	else if (key == A_KEY)
	{
		vars->pos->x -= 10;
		//vars->player->pos->x -= 10;
		//printf("%d\n", vars->player->pos->x);
	}
	else if (key == S_KEY)
	{
		vars->pos->y += 10;
		//vars->player->pos->y += 10;
		//printf("%d\n", vars->player->pos->y);
	}
	else if (key == D_KEY)
	{
		vars->pos->x += 10;
		//vars->player->pos->x += 10;
		//printf("%d\n", vars->pos->x);
	}
	else if (key == ESC)
		return (close(vars));


	update_frame(vars);
	
	return(key);
}

int	update_frame(t_vars *vars)
{
	t_data data;

	data.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	renderMap(data);
	put_circle(&data, POSX + vars->pos->x, POSY + vars->pos->y, 7, 0x00ff0000);

	mlx_put_image_to_window(vars->mlx, vars->window, data.img, 0, 0);

	return (0);
}

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "TESTE PRIMEIRO");
	
	update_frame(&vars);
	mlx_hook(vars.window, 2, 1L<<0, keypressed, &vars);

	
	mlx_loop(vars.mlx);
	return (0);
}


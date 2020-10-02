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

void    renderMap(t_vars *vars, t_data *data)
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
            //render_rectangle(vars, tileX, tileY, tileX + TILE_SIZE, tileY + TILE_SIZE, tileColor);
			put_rect(data, tileX, tileY, tileX + TILE_SIZE, tileY + TILE_SIZE, tileColor);
            j++;
        }
        i++;
    }
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

int		keypressed(int key, t_vars *vars)
{
	int		color;
	t_data	data;
	static int		x;
	static int		y;

	data.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	
	if (key == W_KEY)
	{
		y -= 10;
		printf("%d\n", y);
	}
	else if (key == A_KEY)
	{
		x -= 10;
		printf("%d\n", x);
	}
	else if (key == S_KEY)
	{
		y += 10;
		printf("%d\n", y);
	}
	else if (key == D_KEY)
	{
		x += 10;
		printf("%d\n", x);
	}
	else if (key == ESC)
		return (close(vars));
	//mlx_string_put(vars->mlx, vars->window, POSX + x, POSY + y, 0x0000ffff, "Funciona, carai");
	put_circle(&data, POSX+ x, POSY + y, 10, 0x00ff0000);
	mlx_put_image_to_window(vars->mlx, vars->window, data.img, 0, 0);

	return(key);
}


int		update_frame(t_vars *vars)
{
	int		i;
	int		color;
	t_data	data;

	data.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	//	i = keypressed(key, vars);
	//mlx_hook(vars.window, 2, 1L<<0, keypressed, &vars);
	{ 
		if (i % 3 == 0)
			color = 0x00ff0000;
		else if (i % 3 == 1)
			color = 0x0000ff00;
		else
			color = 0x000000ff;
		put_circle(data.img, 249, 249, 249, color);
	}
	mlx_put_image_to_window(vars->mlx, vars->window, data.img, 0, 0);
	//mlx_loop(vars->mlx);

}


int	main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "TESTE PRIMEIRO");
	img.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	put_circle(&img, POSX, POSY, 10, 0x00ff0000);
	//renderMap(&vars, &img);
	mlx_put_image_to_window(vars.mlx, vars.window, img.img, 0, 0);	
	mlx_hook(vars.window, 2, 1L<<0, keypressed, &vars);
	//mlx_loop_hook(vars.mlx, update_frame, &vars);
	//sethooks(&vars);
	mlx_loop(vars.mlx);
	return (0);
}

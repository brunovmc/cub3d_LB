#include "cub3d.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int	bits_per_pixel;
	int	line_length;
	int	endian;
}		t_data;

typedef struct s_vars {
	void	*mlx;
	void	*window;
}		t_vars;

const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

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

int		keypressed(int key, t_vars *vars)
{
	if (key == 113)
		return(close(&vars));
	else if (key == 119)
		mlx_string_put(vars->mlx, vars->window, 100, 100, 0x00ff0000, "Funciona, carai");
}

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

void    renderMap(t_vars vars, t_data data)
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
			put_rect(&data, tileX, tileY, tileX + TILE_SIZE, tileY + TILE_SIZE, tileColor);
            j++;
        }
        i++;
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
	// (x -a)2 + (y - b)2 = size 2
}

void	print_str(t_vars *vars,  int x, int y, int color, char *str)
{
	mlx_string_put(vars->mlx, vars->window, x, y, color, str);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "TESTE PRIMEIRO");

	img.img = mlx_new_image(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

	//my_pixel_put(&img, 250, 250, 0x0000FF00);
	//put_rect(&img, 0, 0, 500, 500, 0x00FF0000);
	//put_circle(&img, 249, 249, 249, 0x0000FF00);
	renderMap(vars, img);
	mlx_put_image_to_window(vars.mlx, vars.window, img.img, 0, 0);
	//mlx_string_put(vars.mlx, vars.window, 20, 20 , 0x000000FF, "Hi, I am mlx_string_put");
	
	print_str(&vars, 40, 40, 0x00FF0000, "hello from print_str! Im I red?");

	//mlx_key_hook(vars.window, close, &vars);
	
	mlx_hook(vars.window, 2, 1L<<0, keypressed, &vars);
	//sethooks(&vars);
	mlx_loop(vars.mlx);
	return (0);
}
#include "cub3d.h"

int close(t_vars *vars)
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
void my_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void put_rectangle(t_data *data, int x, int y, int size_x, int size_y, int color)
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

void put_line(t_data *data, t_vars *vars, double x, double y, int size, int color)
{
	double dir;
	int i;
	// double new_x;
	// double new_y;

	i = 0;
	//i = vars->player->walk_forward;
	dir = (vars->player->dir * 3.14) / 180;
	while (i < size)
	{
		vars->pos->new_x = (size - i) * cos(dir);
		//printf("new_x = %f\n", vars->pos->new_x);
		vars->pos->new_y = (size - i) * sin(dir);
		//printf("new_y = %f\n", vars->pos->new_y);

		printf("dir = %f\n", vars->player->dir);
		// printf("walk forward = %f\n", vars->player->walk_forward);

		my_pixel_put(data, x + vars->pos->new_x, y + vars->pos->new_y, color);
		// vars->player->dir = dir;
		printf("x + new_x = %f\n", x + vars->pos->new_x);
		printf("y + new_y = %f\n", y + vars->pos->new_y);
		i++;
	}
}

void put_circle(t_data *data, int a, int b, int size, int color)
{
	int x;
	int y;

	x = 0;
	while (x <= (a + size))
	{
		y = 0;
		while (y <= (b + size))
		{
			if ((x - a) * (x - a) + (y - b) * (y - b) <= size * size)
				my_pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

void renderMap(t_data data)
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
			put_rectangle(&data, tileX, tileY, tileX + TILE_SIZE, tileY + TILE_SIZE, tileColor);
			j++;
		}
		i++;
	}
}

// int returnindex(t_vars *vars, char c, int sign)
// {
// 	int i;
// 	int j;
// 	int k;
// 	int h;

// 	i = floor((vars->pos->y + ((sign) * WALK_SPEED) * vars->pos->new_y) / TILE_SIZE);
// 	j = floor((vars->pos->x + ((sign) * WALK_SPEED) * vars->pos->new_x) / TILE_SIZE);
// 	k = floor((vars->pos->y + ((sign) * WALK_SPEED) * vars->pos->new_x) / TILE_SIZE);
// 	h = floor((vars->pos->x + ((sign) * WALK_SPEED) * vars->pos->new_y) / TILE_SIZE);
// 	if (c == 'i')
// 		return  (i);
// 	if (c == 'j')
// 		return (j);
// 	if (c == 'k')
// 		return (k);
// 	if (c == 'h')
// 		return (h);
// }	

void	iscolision(t_vars *vars, char c, int sign)
{
	int i;
	int j;

	if (c == 'w' || c == 's')
	{
		i = floor((vars->pos->y + (sign * WALK_SPEED) * vars->pos->new_y) / TILE_SIZE);
		j = floor((vars->pos->x + (sign * WALK_SPEED) * vars->pos->new_x) / TILE_SIZE);
		if (!(map[i][j] == 1) && map[i][j] == 0)
		{
			vars->pos->x += (sign * WALK_SPEED) * vars->pos->new_x;
			vars->pos->y += (sign * WALK_SPEED) * vars->pos->new_y;
		}
	}
	if (c == 'a' || c == 'd')
	{
		i = floor((vars->pos->y + (-sign * WALK_SPEED) * vars->pos->new_x) / TILE_SIZE);
		j = floor((vars->pos->x + (sign * WALK_SPEED) * vars->pos->new_y) / TILE_SIZE);
		if (!(map[i][j] == 1))
		{
			vars->pos->x += (sign * WALK_SPEED) * vars->pos->new_y;
			vars->pos->y += (-sign * WALK_SPEED) * vars->pos->new_x;
		}
	}
}

void walk_forward(t_vars *vars)
{
	// int i;
	// int j;

	// i = floor((vars->pos->y + WALK_SPEED * vars->pos->new_y) / TILE_SIZE);
	// j = floor((vars->pos->x + WALK_SPEED * vars->pos->new_x) / TILE_SIZE);

	// if (!(map[returnindex(vars, 'i', 1)][returnindex(vars, 'j', 1)] == 1))
	// {
	// 	vars->pos->x += WALK_SPEED * vars->pos->new_x;
	// 	vars->pos->y += WALK_SPEED * vars->pos->new_y;
	// }
	iscolision(vars, 'w', 1);
}

void walk_backward(t_vars *vars)
{
	// if (!(map[returnindex(vars, 'i', -1)][returnindex(vars, 'j', -1)] == 1))
	// {
	// 	vars->pos->x += -WALK_SPEED * vars->pos->new_x;
	// 	vars->pos->y += -WALK_SPEED * vars->pos->new_y;
	// }
	iscolision(vars, 's', -1);
}

void walk_right(t_vars *vars)
{
	// if (!(map[returnindex(vars, 'k', -1)][returnindex(vars, 'h', 1)] == 1))
	// {
	// 	vars->pos->x += -WALK_SPEED * vars->pos->new_y;
	// 	vars->pos->y += WALK_SPEED * vars->pos->new_x;
	// }
	iscolision(vars, 'd', -1);
}

void walk_left(t_vars *vars)
{
	// if (!(map[returnindex(vars, 'k', -1)][returnindex(vars, 'h', 1)] == 1))
	// {
	// 	vars->pos->x += WALK_SPEED * vars->pos->new_y;
	// 	vars->pos->y += -WALK_SPEED * vars->pos->new_x;
	// }
	iscolision(vars, 'a', 1);
}
void rotation_sign(t_vars *vars)
{
	if (vars->player->dir > 360 - ROTATION_SPEED)
		vars->player->dir = 0;
	if (vars->player->dir == -ROTATION_SPEED)
		vars->player->dir = 360 - ROTATION_SPEED;
}

void look_left(t_vars *vars)
{
	//rotation_sign(vars);
	vars->player->dir -= ROTATION_SPEED;
	rotation_sign(vars);
	printf("vars->player->dir = %f\n", vars->player->dir);
}

void look_right(t_vars *vars)
{
	//rotation_sign(vars);
	vars->player->dir += ROTATION_SPEED;
	rotation_sign(vars);
	printf("vars->player->dir %f\n", vars->player->dir);
}

int keypressed(int key, t_vars *vars)
{
	int color;

	if (key == W_KEY)
		walk_forward(vars);
	else if (key == A_KEY)
		walk_left(vars);
	else if (key == S_KEY)
		walk_backward(vars);
	else if (key == D_KEY)
		walk_right(vars);
	else if (key == LEFT_KEY)
		look_left(vars);
	else if (key == RIGHT_KEY)
		look_right(vars);
	else if (key == ESC)
		return (close(vars));

	update_frame(vars);
	return (key);
}

int update_frame(t_vars *vars)
{
	t_data data;

	data.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	//data = alloc_data(vars);
	renderMap(data);
	//renderMap(&vars , &data);
	//my_pixel_put(&data, POSX + x, POSY + y, color);
	//put_rect(&data, vars->pos->x, vars->pos->y, 50, 1, 0x00ff0000);
	put_circle(&data, vars->pos->x, vars->pos->y, 2, 0x00ff0000);
	put_line(&data, vars, vars->pos->x, vars->pos->y, 100, 0x0ff0000);
	mlx_put_image_to_window(vars->mlx, vars->window, data.img, 0, 0);
	return (0);
}

int main(void)
{
	t_vars vars;
	t_point pos;
	t_player player;

	player.dir = 0.0;
	vars.player = &player;
	pos.x = POSX;
	pos.y = POSY;
	vars.pos = &pos;

	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "TESTE PRIMEIRO");

	update_frame(&vars);
	mlx_hook(vars.window, 2, 1L << 0, keypressed, &vars);

	mlx_loop(vars.mlx);
	return (0);
}
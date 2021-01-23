#include "../include/cub3d.h"

void renderMap(t_data data)
{
	int i;
	int j;
	int tileX;
	int tileY;
	int tileColor;

	static int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
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
			put_rectangle(&data, tileX, tileY, tileX, tileY + TILE_SIZE, 0X00000000);
			put_rectangle(&data, tileX, tileY, tileX + TILE_SIZE, tileY, 0X00000000);
			j++;
		}
		i++;
	}
}

int update_frame(t_vars *vars)
{
	t_data data;

	data.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	renderMap(data);
	put_line(&data, vars, vars->pos->x, vars->pos->y, 100, 0x0000ff00);
	put_rays_G(&data, vars, vars->pos->x, vars->pos->y, 0x00ff0000);
	put_circle(&data, vars->pos->x, vars->pos->y, 2, 0x00000000);
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
	//adicionar keyreleased
	mlx_loop(vars.mlx);
	return (0);
}
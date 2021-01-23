#include "../include/cub3d.h"

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
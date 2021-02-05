#include "cub3d.h"

int update_frame(t_vars *vars)
{
	t_data data;

	data.img = mlx_new_image(vars->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	render_map(data);
	//put_line(&data, vars, vars->pos->x, vars->pos->y, 100, 0x0000ff00);
	//put_rays_G(&data, vars, vars->pos->x, vars->pos->y, 0x00ff0000);
	//put_circle(&data, vars->pos->x, vars->pos->y, 2, 0x00000000);
	
	update_player(vars->player);
	put_player(&data, vars->player);
	cast_all_rays(&data, vars->player);
	mlx_put_image_to_window(vars->mlx, vars->window, data.img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_vars		vars;
	t_player 	player;
	t_map		map; //achei melhor lancar map aqui

	vars.player = &player; 
	vars.map = &map;
	map_reader(argc, argv, &vars);

	player.rotation_angle = 2 * PI;
	player.radius = 10;
	player.move_speed = 7.0;
	player.rotation_speed = 7 * (PI / 180);
	player.walk_direction = 0;
	player.turn_direction = 0;


	//vars.player = &player;
	player.x = POSX;
	player.y = POSY;

	vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "TESTE PRIMEIRO");

	update_frame(&vars);
	mlx_hook(vars.window, 2, (1L << 0), keypressed, &vars);
	mlx_hook(vars.window, 3, (1L << 1), keyreleased, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
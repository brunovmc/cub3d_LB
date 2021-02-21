#include "cub3d.h"

int update_frame(t_vars *vars)
{
	t_data data;

	data.img = mlx_new_image(vars->mlx, vars->width, vars->height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	put_rectangle(&data, 0, 0, vars->width, vars->height / 2, vars->map->ceiling);
	put_rectangle(&data, 0, vars->height / 2, vars->width, vars->height, vars->map->floor);
	//put_line(&data, vars, vars->pos->x, vars->pos->y, 100, 0x0000ff00);
	//put_rays_G(&data, vars, vars->pos->x, vars->pos->y, 0x00ff0000);
	//put_circle(&data, vars->pos->x, vars->pos->y, 2, 0x00000000);
	
	update_player(vars);
	update_player_sideways(vars->player, vars);
	put_player(&data, vars->player);
	cast_all_rays(&data, vars->player, vars);
	render_map(vars, data);
	mlx_put_image_to_window(vars->mlx, vars->window, data.img, 0, 0);
	return (0);
}

int main(int argc, char **argv)
{
	t_vars		vars;
	t_player 	player;
	t_map		map; //achei melhor lancar map aqui

	vars = (t_vars) {0};

	vars.player = &player; 
	vars.map = &map;
	
	

	// vars.map->no = '\0';
	// vars.map->so = '\0';
	// vars.map->we = '\0';
	// vars.map->ea = '\0';

	vars.mlx = mlx_init();
	map_reader(argc, argv, &vars);

	//player.rotation_angle = 2 * PI;
	player.radius = 3;
	player.move_speed = 7.0;
	player.rotation_speed = 7 * (PI / 180);
	player.walk_direction = 0;
	player.turn_direction = 0;


	//vars.player = &player;
	//////player.x = POSX;
	//////player.y = POSY;

	// vars.mlx = mlx_init();
	vars.window = mlx_new_window(vars.mlx, vars.width, vars.height, "TESTE PRIMEIRO");

	update_frame(&vars);
	mlx_hook(vars.window, 2, (1L << 0), keypressed, &vars);
	mlx_hook(vars.window, 3, (1L << 1), keyreleased, &vars);
	mlx_hook(vars.window, 17, (1L << 17), ft_close, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
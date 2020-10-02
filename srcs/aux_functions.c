#include "cub3d.h"

void	print_str(t_vars *vars,  int x, int y, int color, char *str)
{
	mlx_string_put(vars->mlx, vars->window, x, y, color, str);
}
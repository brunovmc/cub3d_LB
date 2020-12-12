#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

# define TILE_SIZE 40
# define MAP_NUM_ROWS 10
# define MAP_NUM_COLS 15
# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define ESC 0x00ff1b
# define W_KEY 0x77
# define A_KEY 0x61
# define S_KEY 0x73
# define D_KEY 0x64
# define LEFT_KEY 0xff51
# define RIGHT_KEY 0xff53

# define POSX 200
# define POSY 200

# define ROTATION_SPEED 1.0
# define WALK_SPEED 10

typedef struct s_point {
    double       x;
    double       y;
    double       new_x;
    double       new_y;
    int       color;
}               t_point;

typedef struct s_player {
    double       dir;
    // double          walk_forward;
    // double          walk_backward;
    // int          walk_left;
    // int          walk_right;
    t_point     *pos;
}               t_player;

typedef struct  s_data {
	void	*img;
	char	*addr;
	int	    bits_per_pixel;
	int	    line_length;
	int	    endian;
}		        t_data;

typedef struct  s_vars {
	void	    *mlx;
	void	    *window;
	t_data  	*data;
    t_player    *player;
    t_point     *pos;
}               t_vars;

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

void    my_pixel_put(t_data *data, int x, int y, int color);
void    put_rect(t_data *data, int x, int y, int size_x, int size_y, int color);
void    renderMap(t_data data);
void    put_line(t_data *data, t_vars *vars, double x, double y, int size, int color);
void   	put_rays(t_data *data, t_vars *vars, double x, double y, int color);
void    put_circle(t_data *data, int a, int b, int size, int color);
void    print_str(t_vars *vars,  int x, int y, int color, char *str);
int     close(t_vars *vars);
int     keypressed(int key, t_vars *vars);
void	put_line_G(t_data *data,t_vars *vars, double x, double y, double dir, int color);
int update_frame(t_vars *vars);
    t_data *create(void *mlx);
t_data alloc_data(t_vars *vars);

#endif

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>

// ====  teclas ====
# define ESC 0x00ff1b
# define W_KEY 0x77
# define A_KEY 0x61
# define S_KEY 0x73
# define D_KEY 0x64
# define LEFT_KEY 0xff51
# define RIGHT_KEY 0xff53


//==== NOSSOS DEFINES ====
# define PI 3.141592
# define TRUE 1
# define FALSE 0


// ==== defines gustavo ====
# define TILE_SIZE 64
# define MAP_NUM_ROWS 10
# define MAP_NUM_COLS 15

# define MAX_VALUE 3.40282e+038

# define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
# define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

# define FOV_ANGLE (60 * PI / 180)

# define WALL_STRIP_WIDTH 1
# define NUM_RAYS (WINDOW_WIDTH / WALL_STRIP_WIDTH)

# define MINIMAP_SCALE_FACTOR 1





# define POSX 200
# define POSY 200

# define ROTATION_SPEED 1.0
# define WALK_SPEED 10

typedef struct s_ray {
    float   nexthorztouchx;
    float   nexthorztouchy;
    float   nextverttouchx;
    float   nextverttouchy;
    float   horzwallhitx;
    float   horzwallhity;
    float   vertwallhitx;
    float   vertwallhity;
    float   ystep;
    float   xstep;
    float   horzhitdist;
    float   verthitdist;
    float   wallhitx;
    float   wallhity;
    int     washitvert;
    float   current_ray; //rayangle do gustavo
}              t_ray;

typedef struct s_player {
    float x;
    float y;
    float new_x;
    float new_y;
    int radius;
    int turn_direction; 
    int walk_direction;
    float rotation_angle; //antigo dir
    float move_speed;
    float rotation_speed;
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
}               t_vars;

// const int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
//     {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1},
//     {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
//     {1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
//     {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
// };

int     update_frame(t_vars *vars);
void    my_pixel_put(t_data *data, int x, int y, int color);
void    put_rectangle(t_data *data, int x, int y, int size_x, int size_y, int color);
void    render_map(t_data data);
void    put_circle(t_data *data, int a, int b, int size, int color);
void    print_str(t_vars *vars,  int x, int y, int color, char *str);
int     close(t_vars *vars);
int     keypressed(int key, t_vars *vars);
int     keyreleased(int key, t_vars *vars);
double  distancebetweenpoints(double x1, double y1, double x2, double y2);
void    update_player(t_player *player);
int     has_wall_at(float x, float y);
void    cast_all_rays(t_data *data, t_player *player);
float   ray_size(t_ray *ray, t_player *player);
void    horz_intercept(t_ray *ray, t_player *player);
int     increment_horz_step(t_ray *ray, t_player *player); 
void    vert_intercept(t_ray *ray, t_player *player);
int     increment_vert_step(t_ray *ray, t_player *player);
int     ray_facing_down(float rotation_angle);
int     ray_facing_right(float rotation_angle);
void    put_ray(t_data *data, t_player *player, float angle, float distance);
void    put_player(t_data *data, t_player *player);
float   normalize_angle(float angle);

float   ray_size2(t_ray *ray, t_player *player);
void cast_all_rays2(t_data *data, t_player *player);

#endif

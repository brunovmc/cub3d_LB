#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

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
# define NORTH  (1.5 * PI)
# define SOUTH (0.5 * PI)
# define EAST 0
# define WEST (PI)


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

# define MINIMAP_SCALE_FACTOR 0.35

# define BUFFER_SIZE 40

# define ROTATION_SPEED 1.0
# define WALK_SPEED 10

// mensagens de erro

static char     g_errors[][50] =
{
    "Too few arguments\n",
    "Too many arguments\n",
    "Unknown flag. Did you mean --save?\n",
    "Wrong file type. Must be .cub\n",
    "Map file not found\n",
    //validacao mapa
    "Invalid map file\n",
    "Wrong character in map\n",
    "wrong number of players\n",
    //header
    "Header is invalid\n",
    "Some value is duplicated on header\n",
    //resolucao
    "Something wrong with resolution\n",
    //texture
    "Too many texture arguments\n",
    "File extension must be .xpm\n",
    //rgb
    "Too many rgb arguments\n",
    "Invalid rgb number passed\n",
    "RGB number must be between 0 and 255\n",
};

enum e_errors
{
    MISSING_ARGUMENT,
    TOO_MANY_ARGUMENTS,
    SAVE_TYPO,
    WRONG_FILE_TYPE,
    FILE_NOT_FOUND,
    //validacao mapa
    INVALID_FILE,
    WRONG_CHARACTER,
    WRONG_PLAYER,
    //header
    INVALID_HEADER,
    ALREADY_ASSIGNED,
    //resolucao
    WRONG_RESOLUTION,
    //texture
    TOO_MANY_TXT_ARGS,
    NOT_XPM,
    //rgb
    TOO_MANY_RGB_ARGS,
    WRONG_RGB,
    NOT_RGB_NUMBER
};

typedef struct s_map {
    char     **map;
    char     **grid;
    int      rows;
    int      cols;
    char     *no; 
    char     *so; 
    char     *we; 
    char     *ea;
    char     *s;
    int      quantsprites;
    int      floor;
    int      ceiling;
}              t_map; 

typedef struct s_ray {
    double   nexthorztouchx;
    double   nexthorztouchy;
    double   nextverttouchx;
    double   nextverttouchy;
    double   horzwallhitx;
    double   horzwallhity;
    double   vertwallhitx;
    double   vertwallhity;
    double   ystep;
    double   xstep;
    double   horzhitdist;
    double   verthitdist;
    double   wallhitx;
    double   wallhity;
    int      washitvert;
    double   current_ray; //rayangle do gustavo
    int      foundhorzwallhit;
    int      foundvertwallhit;
    double   x_intercept;
    double   y_intercept;
}              t_ray;

typedef struct s_player {
    float    x;
    float    y;
    float    new_x;
    float    new_y;
    int      radius;
    int      turn_direction; 
    int      walk_direction;
    int      walk_sideways;
    float    rotation_angle; //antigo dir
    float    move_speed;
    float    rotation_speed;
}              t_player;

typedef struct s_data {
	void	 *img;
	char	 *addr;
	int	     bits_per_pixel;
	int	     line_length;
	int	     endian;
}		       t_data;

typedef struct s_vars {
	void	 *mlx;
	void	 *window;
    int      width;
    int      height;
    int      max_width;
    int      max_height;
	t_data   *data;
    t_player *player;
    t_map    *map;
}              t_vars;

int     update_frame(t_vars *vars);
void    my_pixel_put(t_data *data, int x, int y, int color);
void    put_rectangle(t_data *data, int x, int y, int size_x, int size_y, int color);
void    render_map(t_vars *vars, t_data data);
void    render_map2(t_vars *vars, t_data data);
void    put_circle(t_data *data, int a, int b, int size, int color);
void    print_str(t_vars *vars,  int x, int y, int color, char *str);
int     ft_close(t_vars *vars);
int     keypressed(int key, t_vars *vars);
int     keyreleased(int key, t_vars *vars);
double  distancebetweenpoints(double x1, double y1, double x2, double y2);
void    update_player(t_player *player);
void    update_player_sideways(t_player *player);
int     has_wall_at(double x, double y);
void    cast_all_rays(t_data *data, t_player *player);
double  ray_size(t_ray *ray, t_player *player);
void    horz_intercept(t_ray *ray, t_player *player);
void    increment_horz_step(t_ray *ray);
void    vert_intercept(t_ray *ray, t_player *player);
void    increment_vert_step(t_ray *ray);
int     ray_facing_down(double rotation_angle);
int     ray_facing_right(double rotation_angle);
void    put_ray(t_data *data, t_player *player, double angle, double distance);
void    put_player(t_data *data, t_player *player);
double  normalize_angle(double angle);

int     ft_error(int error_num);
int     map_reader(int argc, char **argv, t_vars *vars);
int     read_file(const char *argv, t_vars *vars);
int     check_args(int argc, char **argv);
int     check_header(char *line, t_vars *vars);
int     header_values(t_vars *vars);
int     check_resolution(char *line, t_vars *vars);
int     check_texture(char *line, char c, t_vars *vars);
int     aredigits(char * str);   //colocar na libft?
unsigned long int   rgb_hex(int r, int g, int b);
int     check_rgb(char *line, char c, t_vars *vars);
int     allocate_map(char *line, t_vars *vars);
char    **matrix_buffer(char **map, char *line, int cols);
int     normalize_map(int rows, int cols, t_vars *vars);
int     clear_pointer(char **p);
void    init_header(t_vars *vars);
int     header_full(t_vars *vars);
int     check_character_map(t_vars *vars, char *line);
void    init_player(t_vars *vars,char direction,int x,int y);

int     newline(char *s_line);
char    *cleanline(char **line, char *s_line, int j);
int     get_next_line(int fd, char **line);
void	ft_bzero_gnl(char *str);

#endif

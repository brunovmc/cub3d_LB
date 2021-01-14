#include "../include/cub3d.h"

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

void put_rays_G(t_data *data, t_vars *vars, double x, double y, int color)
{
    double rayAngle = ((vars->player->dir) * 3.14) / 180 - 30 * 3.14 / 180;
    //double rayAngle = dir; //(FOV_ANGLE / 2);

    //COLOCAR NO .h posteriormente
    int WALL_STRIP_WIDTH = 10;
    double NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH;

    int i = 0;
    while (i < NUM_RAYS)
    {
        //if (i % 2 != 0)
        put_line_G(data, vars, vars->pos->x, vars->pos->y, rayAngle, 0x00ff0000);
        //else
        //put_line(data, vars, vars->pos->x, vars->pos->y, 100, 0x0000ff00);

        //rayAngle += 60 / NUM_RAYS;
        rayAngle += 3.14 / 180;
        i++;
    }
}

void put_line_G(t_data *data, t_vars *vars, double x, double y, double dir, int color)
{
    int i;
    int size = 90; //tamanho do raio

    i = 0;
    while (i < size)
    {
        my_pixel_put(data, (x + cos(dir) * i), (y + sin(dir) * i), color);
        i++;
    }
}

void put_line(t_data *data, t_vars *vars, double x, double y, int size, int color)
{
    double dir;
    int i;
    int dist;

    i = 0;
    dir = (vars->player->dir * 3.14) / 180;
    dist = size;
    while (i < dist)
    {

        vars->pos->new_x = (dist - i) * cos(dir);
        vars->pos->new_y = (dist - i) * sin(dir);

        printf("dir = %f\n", vars->player->dir);
        printf("vars->pos->x/TS = %f\n", x / TILE_SIZE);
        printf("vars->pos->y/TS = %f\n", y / TILE_SIZE);

        my_pixel_put(data, (x + vars->pos->new_x), (y + vars->pos->new_y), color);
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

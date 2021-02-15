#include "cub3d.h"

void    render3d_walls(t_vars *vars, t_data *data, double raydistance, double current_ray, int i)
{
    //float   raydistance;
    //float   ray;
    double  distanceprojection;
    double  wallstripheight;
    double  real_wall_dist;

    //i = 0;
    //while (i < vars->map->cols * TILE_SIZE)
    //{
        //ray = rays[i];
        //raydistance = rays;
    real_wall_dist = raydistance * cos(current_ray - vars->player->rotation_angle);

    distanceprojection = fabs((vars->width / 2) / tan((FOV_ANGLE * 180 / PI) / 2));
    wallstripheight = (TILE_SIZE / real_wall_dist) * distanceprojection;
    put_rectangle(data, i * WALL_STRIP_WIDTH,
                  (vars->height / 2) - (wallstripheight / 2),
                  i * WALL_STRIP_WIDTH + WALL_STRIP_WIDTH,
                  (vars->height / 2) - (wallstripheight / 2) + wallstripheight, 0X00FFFFFF);
    // printf("distanceprojection: %f\n", distanceprojection);
    //printf("wallstripheight   : %f\n", wallstripheight);
    // my_pixel_put(vars->data, vars->width / 2, vars->height / 2, 0X0000FF00);
    //put_rectangle(data, 50, 50, 150, 150, 0x00FFFFFF);
    //}

    //return (1);
}
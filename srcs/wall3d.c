#include "cub3d.h"

void    render3d_walls(t_vars *vars, t_data *data, float raydistance, float current_ray, int i, float distanceprojection)
{
    //float   raydistance;
    //float   ray;
    //double  distanceprojection;
    float  wallstripheight;
    float  real_wall_dist;
    //int     i;

    //i = 0;
    //while (i < vars->width)
    //{
        //ray = rays[i];
        //raydistance = rays;
    real_wall_dist = raydistance * cos(current_ray - vars->player->rotation_angle);

    //distanceprojection = (vars->width / 2) / (tan(FOV_ANGLE / 2));
    wallstripheight = (TILE_SIZE / real_wall_dist) * distanceprojection <= vars->height ?
                       (TILE_SIZE / real_wall_dist) * distanceprojection :
                       vars->height;

    put_rectangle(data, i * WALL_STRIP_WIDTH,
                  (vars->height / 2) - (wallstripheight / 2),
                  i * WALL_STRIP_WIDTH + WALL_STRIP_WIDTH,
                  (vars->height / 2) - (wallstripheight / 2) + wallstripheight, 0X00FFFFFF);
    //printf("distanceprojection: %f\n", distanceprojection);
    //printf("wallstripheight   : %f\n", wallstripheight);
    // my_pixel_put(vars->data, vars->width / 2, vars->height / 2, 0X0000FF00);
    //i++;
    //}

    //return (1);
}
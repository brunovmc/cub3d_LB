#include "cub3d.h"

void    render3d_walls(t_vars *vars, double raydistance)
{
    //float   raydistance;
    //float   ray;
    float   distanceprojection;
    float   wallstripheight;
    int     i;

    //i = 0;
    //while (i < vars->map->cols * TILE_SIZE)
    //{
        //ray = rays[i];
        //raydistance = rays;
        distanceprojection = (vars->width/ 2) / tan((FOV_ANGLE * 180/PI) / 2);
        wallstripheight = (TILE_SIZE / raydistance) * distanceprojection;
        put_rectangle(vars->data, i * WALL_STRIP_WIDTH, 
            (vars->height / 2) - (wallstripheight / 2),
            i * WALL_STRIP_WIDTH + WALL_STRIP_WIDTH, 
            (vars->height / 2) - (wallstripheight / 2) + wallstripheight, 0X00FFFFFF);
        printf("distanceprojection: %f\n", distanceprojection);
        printf("wallstripheight   : %f\n", wallstripheight);
        //put_rectangle(vars->data, 50, 50, 150, 150, 0x00FFFFFF);
        i++;
    //}

    //return (1);
}
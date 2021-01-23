#include "../include/cub3d.h"

void    put_rays()
{
    horz_intercept();
}

void    horz_intercept(t_rays *rays, t_player *player)
{
    float ystep;
    float xstep;
    

    rays->y_intercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    rays->y_intercept += ray_facing_down(player->rotation_angle) ? TILE_SIZE : 0;
    rays->x_intercept = player->x + (rays->y_intercept - player->y) 
        / tan(player->rotation_angle);

    ystep = TILE_SIZE;
    ystep *= !ray_facing_down(player->rotation_angle) ? -1 : 1;

    xstep = TILE_SIZE / tan(player->rotation_angle);
    xstep *= (!ray_facing_right(player->rotation_angle) && xstep > 0) ? -1 : 1;
    xstep *= (ray_facing_right(player->rotation_angle) && xstep < 0) ? -1 : 1;

    double nexthorztouchx = xintercept;
    double nexthorztouchy = yintercept;
}

void vert_intercept(t_rays *rays, t_player *player)
{ 
    rays->x_intercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    rays->x_intercept += ray_facing_right(player->rotation_angle) ? TILE_SIZE : 0;
    rays->y_intercept = player->y + (rays->x_intercept - player->x) / tan(player->rotation_angle);
}

int ray_facing_down(int rotation_angle)
{
    return ((rotation_angle > 0 && rotation_angle < PI));
}

int ray_facing_right(int rotation_angle)
{
    return ((rotation_angle < 0.5 * PI || rotation_angle > 1.5 * PI));
}

void put_ray(float distance)
{
    int i;

    i = 0;
    while (i < distance)
    {
        my_pixel_put(data, (x + cos(dir) * i), (y + sin(dir) * i), color);
        i++;
    }
}
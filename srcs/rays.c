#include "cub3d.h"

void    cast_all_rays(t_data *data, t_player *player)
{
    float rayangle;
    float rays[NUM_RAYS];
    int col;
    t_ray ray;

    

    rayangle = normalize_angle(player->rotation_angle) - (FOV_ANGLE / 2);
    col = 0;
    while (col < NUM_RAYS)
    {
        rays[col] = ray_size(&ray, player);
        rayangle += FOV_ANGLE / NUM_RAYS;
        put_ray(data, player, rays[col]);
        col++;
    }
}

float    ray_size(t_ray *ray, t_player *player)
{
    int foundhorzwallhit;
    int foundvertwallhit;

    horz_intercept(ray, player);
    foundhorzwallhit = increment_horz_step(ray, player);
    vert_intercept(ray, player);
    foundvertwallhit = increment_vert_step(ray, player);
    ray->horzhitdist = foundhorzwallhit ? distancebetweenpoints(player->x,
     player->y, ray->horzwallhitx, ray->horzwallhity) : MAX_VALUE;
    ray->verthitdist = foundvertwallhit ? distancebetweenpoints(player->x,
     player->y, ray->vertwallhitx, ray->vertwallhity) : MAX_VALUE;
    if (ray->verthitdist < ray->horzhitdist)
    {
        ray->wallhitx = ray->vertwallhitx;
        ray->wallhity = ray->vertwallhity;
        ray->washitvert = TRUE;
        return (ray->verthitdist);
    }
    else
    {
        ray->wallhitx = ray->horzwallhitx;
        ray->wallhity = ray->horzwallhity;
        ray->washitvert = FALSE;
        return (ray->horzhitdist);
    }
}

void    horz_intercept(t_ray *ray, t_player *player)
{
    float x_intercept;
    float y_intercept;
    
    y_intercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    y_intercept += ray_facing_down(player->rotation_angle) ? TILE_SIZE : 0;
    x_intercept = player->x + (y_intercept - player->y) 
        / tan(player->rotation_angle);
    ray->ystep = TILE_SIZE;
    ray->ystep *= !ray_facing_down(player->rotation_angle) ? -1 : 1;
    ray->xstep = TILE_SIZE / tan(player->rotation_angle);
    ray->xstep *= (!ray_facing_right(player->rotation_angle)
     && ray->xstep > 0) ? -1 : 1;
    ray->xstep *= (ray_facing_right(player->rotation_angle)
     && ray->xstep < 0) ? -1 : 1;
    ray->nexthorztouchx = x_intercept;
    ray->nexthorztouchy = y_intercept;
}

int increment_horz_step(t_ray *ray, t_player *player)
{
    while(ray->nexthorztouchx >= 0 && ray->nexthorztouchx <= WINDOW_WIDTH && 
     ray->nexthorztouchy >= 0 && ray->nexthorztouchy <= WINDOW_HEIGHT)
    {
        if (has_wall_at(ray->horzwallhitx, ray->horzwallhity - (!ray_facing_down(player->rotation_angle) ? 1 : 0)))
        {
           ray->horzwallhitx = ray->nexthorztouchx; 
           ray->horzwallhity = ray->nexthorztouchy;
           return (TRUE); 
        }
        else
        {
            ray->nexthorztouchx += ray->xstep;
            ray->nexthorztouchy += ray->ystep;
        }
    }
    return (FALSE);
}

void vert_intercept(t_ray *ray, t_player *player)
{ 
    float   x_intercept;
    float   y_intercept;

    x_intercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    x_intercept += ray_facing_right(player->rotation_angle) ? TILE_SIZE : 0;
    y_intercept = player->y + (x_intercept - player->x) / tan(player->rotation_angle);
    ray->xstep = TILE_SIZE;
    ray->xstep *= !ray_facing_right(player->rotation_angle) ? -1 : 1;
    ray->ystep = TILE_SIZE * tan(player->rotation_angle);
    ray->ystep *= (!ray_facing_down(player->rotation_angle) && ray->ystep > 0) ? -1 : 1;
    ray->ystep *= (ray_facing_down(player->rotation_angle) && ray->ystep < 0) ? -1 : 1;
    ray->nextverttouchx = x_intercept;
    ray->nextverttouchy = y_intercept;
}

int increment_vert_step(t_ray *ray, t_player *player)
{
    while (ray->nextverttouchx >= 0 && ray->nextverttouchx <= WINDOW_WIDTH &&
           ray->nextverttouchy >= 0 && ray->nextverttouchy <= WINDOW_HEIGHT)
    {
        if (has_wall_at(ray->vertwallhitx, ray->vertwallhity - (!ray_facing_right(player->rotation_angle) ? 1 : 0)))
        {
            ray->vertwallhitx = ray->nextverttouchx;
            ray->vertwallhity = ray->nextverttouchy;
            return (TRUE);
        }
        else
        {
            ray->nextverttouchx += ray->xstep;
            ray->nextverttouchy += ray->ystep;
        }
    }
    return (FALSE);
}

int ray_facing_down(int rotation_angle)
{
    return ((rotation_angle > 0 && rotation_angle < PI));
}

int ray_facing_right(int rotation_angle)
{
    return ((rotation_angle < 0.5 * PI || rotation_angle > 1.5 * PI));
}

void put_ray(t_data *data, t_player *player, float distance)
{
    int i;

    i = 0;
    while (i < distance)
    {
        my_pixel_put(data, (player->x + cos(player->rotation_angle) * i),
                     (player->y + sin(player->rotation_angle) * i), 0x00ff0000);
        i++;
    }
}
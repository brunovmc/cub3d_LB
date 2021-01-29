#include "cub3d.h"

void    cast_all_rays(t_data *data, t_player *player)
{
    float rayangle;
    float rays[NUM_RAYS];
    int col;
    t_ray ray;

    ray.current_ray = normalize_angle(player->rotation_angle) - (FOV_ANGLE / 2);
    //ray.current_ray = normalize_angle(player->rotation_angle);
    col = 0;
    while (col < NUM_RAYS)
    //while (col < 1)
    {   
        rays[col] = ray_size(&ray, player);
        //printf("ray[%d]: %f\n", col, rays[col]);
        put_ray(data, player, ray.current_ray, rays[col]);
        ray.current_ray = normalize_angle(ray.current_ray + FOV_ANGLE / NUM_RAYS);
        col++;
    }
}

float    ray_size(t_ray *ray, t_player *player)
{
    int foundhorzwallhit;
    int foundvertwallhit;

    horz_intercept(ray, player);
    foundhorzwallhit = increment_horz_step(ray, player);
    //printf("foundhorz: %i\n", foundhorzwallhit);
    vert_intercept(ray, player);
    foundvertwallhit = increment_vert_step(ray, player);
    //printf("foundvert: %i\n", foundvertwallhit);
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
    y_intercept += ray_facing_down(ray->current_ray) ? TILE_SIZE : 0;
    x_intercept = player->x + (y_intercept - player->y) 
        / tan(ray->current_ray);
    ray->ystep = TILE_SIZE;
    ray->ystep *= !ray_facing_down(ray->current_ray) ? -1 : 1;
    ray->xstep = TILE_SIZE / tan(ray->current_ray);
    ray->xstep *= (!ray_facing_right(ray->current_ray)
     && ray->xstep > 0) ? -1 : 1;
    ray->xstep *= (ray_facing_right(ray->current_ray)
     && ray->xstep < 0) ? -1 : 1;
    ray->nexthorztouchx = x_intercept;
    ray->nexthorztouchy = y_intercept;
    //printf("nexthorztouchx: %f - nexthorztouchy: %f\n", ray->nexthorztouchx, ray->nexthorztouchy);
}

int increment_horz_step(t_ray *ray, t_player *player)
{
    //printf("facingdown: %i\n", ray_facing_down(ray->current_ray));
    //printf("nexthorzx: %f - nexthorzy: %f\n", ray->nexthorztouchx, ray->nexthorztouchy);
    int up_or_down = !ray_facing_down(ray->current_ray) ? 1 : 0;
    while(ray->nexthorztouchx >= 0 && ray->nexthorztouchx <= WINDOW_WIDTH && 
     ray->nexthorztouchy >= 0 && ray->nexthorztouchy <= WINDOW_HEIGHT)
    {
        if (has_wall_at(ray->nexthorztouchx, ray->nexthorztouchy - up_or_down))
        {
           ray->horzwallhitx = ray->nexthorztouchx; 
           ray->horzwallhity = ray->nexthorztouchy;
           //printf("horzwallhitx: %f - horzwallhity: %f\n", ray->horzwallhitx, ray->horzwallhity);
           break;
           //return (TRUE); 
        }
        else
        {
            ray->nexthorztouchx += ray->xstep;
            ray->nexthorztouchy += ray->ystep;
           //printf("AAAAAAA\n");
        }
    }
    return (TRUE);
}

void vert_intercept(t_ray *ray, t_player *player)
{ 
    float   x_intercept;
    float   y_intercept;

    x_intercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    x_intercept += ray_facing_right(ray->current_ray) ? TILE_SIZE : 0;
    y_intercept = player->y + (x_intercept - player->x) / tan(ray->current_ray);
    ray->xstep = TILE_SIZE;
    ray->xstep *= !ray_facing_right(ray->current_ray) ? -1 : 1;
    ray->ystep = TILE_SIZE * tan(ray->current_ray);
    ray->ystep *= (!ray_facing_down(ray->current_ray) && ray->ystep > 0) ? -1 : 1;
    ray->ystep *= (ray_facing_down(ray->current_ray) && ray->ystep < 0) ? -1 : 1;
    ray->nextverttouchx = x_intercept;
    ray->nextverttouchy = y_intercept;
    //printf("nextverttouchx: %f - nextverttouchy: %f\n", ray->nextverttouchx, ray->nextverttouchy);

}

int increment_vert_step(t_ray *ray, t_player *player)
{
    int left_or_right = !ray_facing_right(ray->current_ray) ? 1 : 0;
    //int i = 0;
    while (ray->nextverttouchx >= 0 && ray->nextverttouchx <= WINDOW_WIDTH &&
           ray->nextverttouchy >= 0 && ray->nextverttouchy <= WINDOW_HEIGHT)
    {
        //printf("i: %i\n", i++);
        if (has_wall_at(ray->nextverttouchx - left_or_right, ray->nextverttouchy))
        {
            ray->vertwallhitx = ray->nextverttouchx;
            ray->vertwallhity = ray->nextverttouchy;
            //printf("vertwallhitx: %f - vertwallhity: %f\n", ray->vertwallhitx, ray->vertwallhity);
            break;
            //return (TRUE);
        }
        else
        {
            //printf("xstep: %f , ystep: %f\n", ray->xstep, ray->ystep);
            ray->nextverttouchx += ray->xstep;
            ray->nextverttouchy += ray->ystep;
        }
    }
    return (TRUE);
}

int ray_facing_down(int rotation_angle)
{
    return ((rotation_angle > 0 && rotation_angle < PI));
}

int ray_facing_right(int rotation_angle)
{
    return ((rotation_angle < 0.5 * PI || rotation_angle > 1.5 * PI));
}

void put_ray(t_data *data, t_player *player, float angle, float distance)
{
    int i;

    i = 0;
    while (i < distance)
    {
        my_pixel_put(data, (player->x + cos(angle) * i),
                     (player->y + sin(angle) * i), 0x00ff0000);
        i++;
    }
}
#include "cub3d.h"

void cast_all_rays2(t_data *data, t_player *player)
{
    double   rays[NUM_RAYS];
    int     col;
    t_ray   ray;

    ray.current_ray = normalize_angle(player->rotation_angle) - (FOV_ANGLE / 2);
    col = 0;
    while(col < NUM_RAYS)
    {
        rays[col] = ray_size2(&ray, player);
        put_ray(data, player, ray.current_ray, rays[col]);
        ray.current_ray = normalize_angle(ray.current_ray + FOV_ANGLE / NUM_RAYS);
        col++;
    }

}

double ray_size2(t_ray *ray, t_player *player)
{
    //PRIMEIRA INTERSECÇÃO HORIZONTAL

    int foundhorzwallhit;
    double y_intercept;
    double x_intercept;

    foundhorzwallhit = FALSE;

    y_intercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    y_intercept += ray_facing_down(ray->current_ray) ? TILE_SIZE : 0;
    x_intercept = player->x + (y_intercept - player->y) / tan(ray->current_ray);
    ray->ystep = TILE_SIZE;
    ray->ystep *= !ray_facing_down(ray->current_ray) ? -1 : 1;
    ray->xstep = TILE_SIZE / tan(ray->current_ray);
    ray->xstep *= (!ray_facing_right(ray->current_ray) && ray->xstep > 0) ? -1 : 1;
    ray->xstep *= (ray_facing_right(ray->current_ray) && ray->xstep < 0) ? -1 : 1;

    // INTERSECÇÃO HORIZONTAL COM O GRID

    ray->nexthorztouchx = x_intercept;
    ray->nexthorztouchy = y_intercept;

    while(ray->nexthorztouchx >= 0 &&  ray->nexthorztouchx <= WINDOW_WIDTH 
        && ray->nexthorztouchy >= 0 && ray->nexthorztouchy <= WINDOW_HEIGHT)
    {
        if (has_wall_at(ray->nexthorztouchx, 
            ray->nexthorztouchy - (!ray_facing_down(ray->current_ray) ? 1 : 0)))
        {
            foundhorzwallhit = TRUE;
            ray->horzwallhitx = ray->nexthorztouchx;
            ray->horzwallhity = ray->nexthorztouchy;
            break;
        }
        else 
        {
            ray->nexthorztouchx += ray->xstep;
            ray->nexthorztouchy += ray->ystep;
        }
    }

    //PRIMEIRA INTERSECÇÃO VERTICAL

    int foundvertwallhit;
    //double y_intercept;
    //double x_intercept;

    foundvertwallhit = FALSE;

    x_intercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    x_intercept += ray_facing_right(ray->current_ray) ? TILE_SIZE : 0;
    y_intercept = player->y + (x_intercept - player->x) * tan(ray->current_ray);
    ray->xstep = TILE_SIZE;
    ray->xstep *= !ray_facing_right(ray->current_ray) ? -1 : 1;
    ray->ystep = TILE_SIZE * tan(ray->current_ray);
    ray->ystep *= (!ray_facing_down(ray->current_ray) && ray->ystep > 0) ? -1 : 1;
    ray->ystep *= (ray_facing_down(ray->current_ray) && ray->ystep < 0) ? -1 : 1;

    //INTERSECÇÃO VERTICAL COM O GRID

    ray->nextverttouchx = x_intercept;
    ray->nextverttouchy = y_intercept;

    while(ray->nextverttouchx >= 0 &&  ray->nextverttouchx <= WINDOW_WIDTH 
        && ray->nextverttouchy >= 0 && ray->nextverttouchy <= WINDOW_HEIGHT)
    {
        if (has_wall_at(ray->nextverttouchx - (!ray_facing_right(ray->current_ray) ? 1 : 0), 
            ray->nextverttouchy))
        {
            foundvertwallhit = TRUE;
            ray->vertwallhitx = ray->nextverttouchx;
            ray->vertwallhity = ray->nextverttouchy;
            break;
        }
        else 
        {
            ray->nextverttouchx += ray->xstep;
            ray->nextverttouchy += ray->ystep;
        }
    }

    // CÁLCULO DA DISTÂNCIA HORIZONTAL COM O MURO

    ray->horzhitdist = (foundhorzwallhit) ? 
    distancebetweenpoints(player->x, player->y,
     ray->horzwallhitx, ray->horzwallhity) : MAX_VALUE;
    ray->verthitdist = (foundvertwallhit) ? 
    distancebetweenpoints(player->x, player->y,
     ray->vertwallhitx, ray->vertwallhity) : MAX_VALUE;

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
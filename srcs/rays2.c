#include "cub3d.h"

void cast_all_rays2(t_data *data, t_player *player)
{
    float    rays[NUM_RAYS];
    int     col;
    t_ray   ray;

    ray.current_ray = normalize_angle(player->rotation_angle) - (FOV_ANGLE / 2);
    col = 0;
    while(col < NUM_RAYS)
    {
        rays[col] = ray_size2(&ray, player);
        ray.current_ray += FOV_ANGLE / NUM_RAYS;
        put_ray(data, player, ray.current_ray, rays[col]);
        col++;
    }

}

float ray_size2(t_ray *ray, t_player *player)
{
    int foundhorzwallhit;
    float y_intercept;
    float x_intercept;

    y_intercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    y_intercept += ray_facing_down(ray->current_ray) ? TILE_SIZE : 0;
    x_intercept = player->x + (y_intercept - player->y) / tan(ray->current_ray);
    ray->ystep = TILE_SIZE;
    ray->ystep *= !ray_facing_down(ray->current_ray) ? -1 : 1;
    ray->xstep = TILE_SIZE / tan(ray->current_ray);
    ray->xstep *= (!ray_facing_right(ray->current_ray) && ray->xstep > 0) ? -1 : 1;
    ray->xstep *= (ray_facing_right(ray->current_ray) && ray->xstep < 0) ? -1 : 1;

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

    ray->horzhitdist = (foundhorzwallhit) ? 
    distancebetweenpoints(player->x, player->y,
     ray->horzwallhitx, ray->horzwallhity) : MAX_VALUE;

    return (ray->horzhitdist);
}
#include "cub3d.h"

void    cast_all_rays(t_data *data, t_player *player, t_vars *vars)
{
    double rayangle;
    //double rays[NUM_RAYS];
    double rays[vars->width];
    int col;
    t_ray ray;

    //vars->player->tilex = vars->width / vars->map->cols;
    //vars->player->tiley = vars->height / vars->map->rows;
    ray.current_ray = normalize_angle(player->rotation_angle) - (FOV_ANGLE / 2);
    col = 0;
    //while (col < NUM_RAYS)
    // printf("max width = %i\n", vars->max_width);
    // printf("width = %i\n", vars->width);
    // printf("cols * tile  = %i\n", vars->map->cols * TILE_SIZE);
    while (col < vars->width)
    {   
        rays[col] = ray_size(&ray, player, vars);
        put_ray(data, player, ray.current_ray, rays[col]);
        render3d_walls(vars, data, rays[col], ray.current_ray, col);
        //ray.current_ray = normalize_angle(ray.current_ray + FOV_ANGLE / NUM_RAYS);
        // my_pixel_put(data, 1200, 600, 0X0000FF00);

        ray.current_ray = normalize_angle(ray.current_ray + FOV_ANGLE / vars->width);

        col++;
    }
    // printf("rays col[0] = %f\n", rays[0]);
    // printf("rays col[1] = %f\n", rays[1]);
    // printf("rays col[col -1] = %f\n", rays[col - 1]);
    //return(render3d_walls(vars, rays));
}

double    ray_size(t_ray *ray, t_player *player, t_vars *vars)
{
    horz_intercept(ray, player, vars);
    increment_horz_step(ray, vars);
    vert_intercept(ray, player, vars);
    increment_vert_step(ray, vars);
    ray->horzhitdist = (ray->foundhorzwallhit) ? 
    distancebetweenpoints(player->x, player->y,
     ray->horzwallhitx, ray->horzwallhity) : MAX_VALUE;
    ray->verthitdist = (ray->foundvertwallhit) ? 
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

void    horz_intercept(t_ray *ray, t_player *player, t_vars *vars)
{
    ray->foundhorzwallhit = FALSE;
    ray->y_intercept = floor(player->y / TILE_SIZE) * TILE_SIZE;
    ray->y_intercept += ray_facing_down(ray->current_ray) ? TILE_SIZE : 0;
    ray->x_intercept = player->x + (ray->y_intercept - player->y) / tan(ray->current_ray);
    ray->ystep = TILE_SIZE;
    ray->ystep *= !ray_facing_down(ray->current_ray) ? -1 : 1;
    ray->xstep = TILE_SIZE / tan(ray->current_ray);
    ray->xstep *= (!ray_facing_right(ray->current_ray) && ray->xstep > 0) ? -1 : 1;
    ray->xstep *= (ray_facing_right(ray->current_ray) && ray->xstep < 0) ? -1 : 1;
}

void increment_horz_step(t_ray *ray, t_vars *vars)
{
    ray->nexthorztouchx = ray->x_intercept;
    ray->nexthorztouchy = ray->y_intercept;
    while (ray->nexthorztouchx >= 0 && ray->nexthorztouchx < vars->width && ray->nexthorztouchy >= 0 && ray->nexthorztouchy < vars->height)
    {
        if (has_wall_at(ray->nexthorztouchx,
                        ray->nexthorztouchy - (!ray_facing_down(ray->current_ray) ? 1 : 0), vars) == '1')
        {
            ray->foundhorzwallhit = TRUE;
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
}

void vert_intercept(t_ray *ray, t_player *player, t_vars *vars)
{
    ray->foundvertwallhit = FALSE;
    ray->x_intercept = floor(player->x / TILE_SIZE) * TILE_SIZE;
    ray->x_intercept += ray_facing_right(ray->current_ray) ? TILE_SIZE : 0;
    ray->y_intercept = player->y + (ray->x_intercept - player->x) * tan(ray->current_ray);
    ray->xstep = TILE_SIZE;
    ray->xstep *= !ray_facing_right(ray->current_ray) ? -1 : 1;
    ray->ystep = TILE_SIZE * tan(ray->current_ray);
    ray->ystep *= (!ray_facing_down(ray->current_ray) && ray->ystep > 0) ? -1 : 1;
    ray->ystep *= (ray_facing_down(ray->current_ray) && ray->ystep < 0) ? -1 : 1;
}

void increment_vert_step(t_ray *ray, t_vars *vars)
{
    ray->nextverttouchx = ray->x_intercept;
    ray->nextverttouchy = ray->y_intercept;
    while (ray->nextverttouchx >= 0 && ray->nextverttouchx < vars->width && ray->nextverttouchy >= 0 && ray->nextverttouchy < vars->height)
    {
        if (has_wall_at(ray->nextverttouchx - (!ray_facing_right(ray->current_ray) ? 1 : 0),
                        ray->nextverttouchy, vars) == '1')
        {
            ray->foundvertwallhit = TRUE;
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
}

int ray_facing_down(double rotation_angle)
{
    return ((rotation_angle > 0 && rotation_angle < PI));
}

int ray_facing_right(double rotation_angle)
{
    return ((rotation_angle < 0.5 * PI || rotation_angle > 1.5 * PI));
}

void put_ray(t_data *data, t_player *player, double angle, double distance)
{
    int i;

    i = 0;
    while (i < distance)
    {
        my_pixel_put(data, (player->x + cos(angle) * i) * MINIMAP_SCALE_FACTOR ,
                     (player->y + sin(angle) * i) * MINIMAP_SCALE_FACTOR, 0x00ff0000);
        i++;
    }
}
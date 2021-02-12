#include "cub3d.h"

void update_player(t_player *player)
{
    double move_step;

    player->rotation_angle += player->turn_direction * player->rotation_speed;
    if (player->walk_direction != 0)
        move_step = player->walk_direction * player->move_speed;
    if (player->walk_sideways != 0)
        move_step = player->move_speed;
    player->new_x = player->x + cos(player->rotation_angle - player->walk_sideways * PI/2) * move_step;
    player->new_y = player->y + sin(player->rotation_angle - player->walk_sideways * PI/2) * move_step;
    if (!has_wall_at(player->new_x, player->new_y))
    {
        player->x = player->new_x;
        player->y = player->new_y;
    }
}

double normalize_angle(double angle)
{
    angle = remainder(angle, 2 * PI);
    if (angle < 0)
        angle += (2 * PI);
    return (angle);
}

int keypressed(int key, t_vars *vars)
{
    int color;

    if (key == W_KEY)
        vars->player->walk_direction = +1;
    else if (key == A_KEY)
        vars->player->walk_sideways = +1;
    else if (key == S_KEY)
        vars->player->walk_direction = -1;
    else if (key == D_KEY)
        vars->player->walk_sideways = -1;
    else if (key == LEFT_KEY)
        vars->player->turn_direction = -1;
    else if (key == RIGHT_KEY)
        vars->player->turn_direction = +1;
    else if (key == ESC)
        return (ft_close(vars));
    update_frame(vars);
    return (key);
}

int keyreleased(int key, t_vars *vars)
{
    int color;

    if (key == W_KEY)
        vars->player->walk_direction = 0;
    else if (key == A_KEY)
        vars->player->walk_sideways = 0;
    else if (key == S_KEY)
        vars->player->walk_direction = 0;
    else if (key == D_KEY)
        vars->player->walk_sideways = 0;
    else if (key == LEFT_KEY)
        vars->player->turn_direction = 0;
    else if (key == RIGHT_KEY)
        vars->player->turn_direction = 0;
    update_frame(vars);
    return (key);
}
#include "../include/cub3d.h"

void iscolision(t_vars *vars, char c, int sign)
{
    int i;
    int j;

    int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    if (c == 'w' || c == 's')
    {
        i = floor((vars->pos->y + (sign * WALK_SPEED) * vars->pos->new_y) / TILE_SIZE);
        j = floor((vars->pos->x + (sign * WALK_SPEED) * vars->pos->new_x) / TILE_SIZE);
        if (!(map[i][j] == 1))
        {
            vars->pos->x += (sign * WALK_SPEED) * vars->pos->new_x;
            vars->pos->y += (sign * WALK_SPEED) * vars->pos->new_y;
        }
    }
    if (c == 'a' || c == 'd')
    {
        i = floor((vars->pos->y + (-sign * WALK_SPEED) * vars->pos->new_x) / TILE_SIZE);
        j = floor((vars->pos->x + (sign * WALK_SPEED) * vars->pos->new_y) / TILE_SIZE);
        if (!(map[i][j] == 1))
        {
            vars->pos->x += (sign * WALK_SPEED) * vars->pos->new_y;
            vars->pos->y += (-sign * WALK_SPEED) * vars->pos->new_x;
        }
    }
}

int iscolision2(double posx, double posy)
{
    int i;
    int j;

    int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    i = floor((posy / TILE_SIZE));
    j = floor((posx / TILE_SIZE));
    if (!(map[i][j] == 1))
        return (1);
    return (0);
}

void walk_forward(t_vars *vars)
{
    iscolision(vars, 'w', 1);
}

void walk_backward(t_vars *vars)
{
    iscolision(vars, 's', -1);
}

void walk_right(t_vars *vars)
{
    iscolision(vars, 'd', -1);
}

void walk_left(t_vars *vars)
{
    iscolision(vars, 'a', 1);
}
void rotation_sign(t_vars *vars)
{
    if (vars->player->dir > 360 - ROTATION_SPEED)
        vars->player->dir = 0;
    if (vars->player->dir == -ROTATION_SPEED)
        vars->player->dir = 360 - ROTATION_SPEED;
}

void look_left(t_vars *vars)
{
    vars->player->dir -= ROTATION_SPEED;
    rotation_sign(vars);
    //printf("vars->player->dir = %f\n", vars->player->dir);
}

void look_right(t_vars *vars)
{
    vars->player->dir += ROTATION_SPEED;
    rotation_sign(vars);
    //printf("vars->player->dir %f\n", vars->player->dir);
}

int keypressed(int key, t_vars *vars)
{
    int color;

    if (key == W_KEY)
        walk_forward(vars);
    else if (key == A_KEY)
        walk_left(vars);
    else if (key == S_KEY)
        walk_backward(vars);
    else if (key == D_KEY)
        walk_right(vars);
    else if (key == LEFT_KEY)
        look_left(vars);
    else if (key == RIGHT_KEY)
        look_right(vars);
    else if (key == ESC)
        return (close(vars));

    update_frame(vars);
    return (key);
}

#include "../include/cub3d.h"

void update_player()//recebe struc do player
{
    float move_step;

    player->rotation_angle += player->turn_direction * player->rotation_speed;
    move_step =  player->walk_direction * player->move_speed;
    player->new_x = player->x + cos(player->rotation_angle) * move_step;
    player->new_y = player->y + sin(player->rotation_angle) * move_step;
    if (!has_wall_at(player->new_x, player->new_y))
    {
        player->x = player->new_x;
        player->y = player->new_y;
    }
}

float normalize_angle(float angle)
{
    angle = fmod(angle, (2 * PI));
    if (angle < 0)
        angle = angle + 2 * PI;
    return (angle);
}

void render_player(t_data data, t_player *player)
{
    // renderizar o player circulo + posicao;
    put_player(&data, &player);
    put_rays();
}

int keypressed(int key, t_vars *vars)
{
    int color;

    if (key == W_KEY)
        player->walk_direction = +1;
    else if (key == A_KEY)
        walk_left(vars);
    else if (key == S_KEY)
        player->walk_direction = -1;
    else if (key == D_KEY)
        walk_right(vars);
    else if (key == LEFT_KEY)
        player->turn_direction = -1;
    else if (key == RIGHT_KEY)
        player->turn_direction = +1;
    else if (key == ESC)
        return (close(vars));
    update_frame(vars);
    return (key);
}

int keyreleased(int key, t_vars *vars)
{
    int color;

    if (key == W_KEY)
        player->walk_direction = 0;
    else if (key == A_KEY)
        walk_left(vars);
    else if (key == S_KEY)
        player->walk_direction = 0;
    else if (key == D_KEY)
        walk_right(vars);
    else if (key == LEFT_KEY)
        player->turn_direction = 0;
    else if (key == RIGHT_KEY)
        player->turn_direction = 0;
    update_frame(vars);
    return (key);
}

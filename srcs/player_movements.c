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

void render_player()
{
    // renderizar o player circulo + posicao;
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

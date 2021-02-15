#include "cub3d.h"

// porque essa funcao funciona???
void my_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void put_rectangle(t_data *data, int x, int y, int size_x, int size_y, int color)
{
    int init_x;

    init_x = x;
    while (y < size_y)
    {
        x = init_x;
        while (x < size_x)
        {
            my_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
}

double distancebetweenpoints(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void put_player(t_data *data, t_player *player)
{
    int x;
    int y;
    int mini_x;
    int mini_y;

    x = 0;
    while (x <= (player->x + player->radius))
    {
        y = 0;
        while (y <= (player->y + player->radius))
        {
            if ((x - player->x) * (x - player->x) + (y - player->y) * 
                (y - player->y) <= player->radius * player->radius)
                {
                    mini_x = x * MINIMAP_SCALE_FACTOR;
                    mini_y = y * MINIMAP_SCALE_FACTOR;
                    my_pixel_put(data, mini_x, mini_y, 0x00000000);
                }
                
            y++;
        }
        x++;
    }
}

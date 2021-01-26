#include "cub3d.h"

int has_wall_at(float x, float y) //adicionar argumento com grid aka mapa
{
    int grid[MAP_NUM_ROWS][MAP_NUM_COLS] = {
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
    int map_grid_index_x;
    int map_grid_index_y;

    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
        return (TRUE);
    map_grid_index_x = floor(x / TILE_SIZE);
    map_grid_index_y = floor(y / TILE_SIZE);

    return (grid[map_grid_index_y][map_grid_index_x] != 0);
}

void render_map(t_data data) //eventualmente mapa como argumento
{
    int i;
    int k;
    int tile_x;
    int tile_y;
    int tile_color;

    int grid[MAP_NUM_ROWS][MAP_NUM_COLS] = {
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

    i = 0;
    while (i < MAP_NUM_ROWS)
    {
        k = 0;
        while (k < MAP_NUM_COLS)
        {
            tile_x = (k * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
            tile_y = (i * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
            tile_color = grid[i][k] == 0 ? 0X00FFFFFF : 0X00000000;
            put_rectangle(&data, tile_x, tile_y, tile_x + TILE_SIZE, tile_y + TILE_SIZE, tile_color);
            put_rectangle(&data, tile_x, tile_y, tile_x, tile_y + TILE_SIZE, 0X00000000);
            put_rectangle(&data, tile_x, tile_y, tile_x + TILE_SIZE, tile_y, 0X00000000);
            k++;
        }
        i++;
    }
}
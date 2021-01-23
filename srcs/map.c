#include "../include/cub3d.h"

has_wall_at(float x, float y) //adicionar argumento com grid aka mapa
{
    int map_grid_index_x;
    int map_grid_index_y;

    if (x < 0 || x > WINDOW_WIDTH || y < 0 || y > WINDOW_HEIGHT)
        return (TRUE);
    map_grid_index_x = floor(x / TILE_SIZE);
    map_grid_index_y = floor(y / TILE_SIZE);

    return (grid[map_grid_index_y][map_grid_index_x] != 0);
}

void render_map()
{
    int i;
    int k;
    int tile_x;
    int tile_y;
    int tile_color;

    i = 0;
    while (i < MAP_NUM_ROWS)
    {
        k = 0;
        while (k < MAP_NUM_COLS)
        {
            tile_x = (k * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
            tile_y = (i * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
            tile_color = grid[i][k] == 1 ? "#222" : "#fff";
            put_rect(tile_x, tile_y, MINIMAP_SCALE_FACTOR * TILE_SIZE,
             MINIMAP_SCALE_FACTOR * TILE_SIZE);
                k++;
        }
        i++;
    }
}

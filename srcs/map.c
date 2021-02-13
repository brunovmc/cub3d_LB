#include "cub3d.h"

int has_wall_at(t_vars *vars, double x, double y) //adicionar argumento com grid aka mapa
{
    int map_grid_index_x;
    int map_grid_index_y;

    if (x < 0 || x > vars->width || y < 0 || y > vars->height)
        return (TRUE);
    map_grid_index_x = floor(x / TILE_SIZE);
    map_grid_index_y = floor(y / TILE_SIZE);
    //if (grid[map_grid_index_y][map_grid_index_x] != 0)
    //    printf("grid[x][y]: %i\n", grid[map_grid_index_y][map_grid_index_x]);

    return (vars->map->grid[map_grid_index_y][map_grid_index_x] != 0);
}

void render_map(t_vars *vars, t_data data) //eventualmente mapa como argumento
{
    int i;
    int k;
    int tile_x;
    int tile_y;
    int tile_color;

    i = 0;
    while (i < vars->map->rows)
    {
        k = 0;
        while (k < vars->map->cols)
        {
            tile_x = (k * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
            tile_y = (i * TILE_SIZE) * MINIMAP_SCALE_FACTOR;
            tile_color = vars->map->grid[i][k] == 0 ? 0X00FFFFFF : 0X00000000;
            put_rectangle(&data, tile_x, tile_y, tile_x + TILE_SIZE, tile_y + TILE_SIZE, tile_color);
            put_rectangle(&data, tile_x, tile_y, tile_x, tile_y + TILE_SIZE, 0X00000000);
            put_rectangle(&data, tile_x, tile_y, tile_x + TILE_SIZE, tile_y, 0X00000000);
            k++;
        }
        i++;
    }
}
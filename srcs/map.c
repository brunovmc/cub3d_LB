#include "cub3d.h"

char has_wall_at(double x, double y, t_vars *vars) //adicionar argumento com grid aka mapa
{
    int map_grid_index_x;
    int map_grid_index_y;

    if (x < 0 || x > vars->map->cols * TILE_SIZE || y < 0 || y > vars->map->rows * TILE_SIZE)
        return (TRUE);
    map_grid_index_x = floor(x / TILE_SIZE);
    map_grid_index_y = floor(y / TILE_SIZE);

    //printf("grid[%i][%i]: %c\n", map_grid_index_y, map_grid_index_x, vars->map->cols * TILE_SIZE);
    return (vars->map->grid[map_grid_index_y][map_grid_index_x]);
}

void render_map(t_vars *vars, t_data data) //eventualmente mapa como argumento
{
    int     i;
    int     k;
    int     tile_x;
    int     tile_y;

    i = 0;
    while (i < vars->map->rows)
    {
        k = 0;
        while (k < vars->map->cols)
        {
            tile_x = (k * TILE_SIZE);
            tile_y = (i * TILE_SIZE);
            if (vars->map->grid[i][k] == '1')
                put_rectangle(&data, tile_x * MINIMAP_SCALE_FACTOR, 
                tile_y * MINIMAP_SCALE_FACTOR, 
                (tile_x + TILE_SIZE) * MINIMAP_SCALE_FACTOR, 
                (tile_y + TILE_SIZE) * MINIMAP_SCALE_FACTOR, 0X00FFFFFF);
            k++;
        }
        i++;
    }
}

void render_map2(t_vars *vars, t_data data) //eventualmente mapa como argumento
{
    int     tile_x;
    int     tile_y;
    int     i;
    int     j;

    printf("\n\n\n\n\n");

    i = 0;
    while (i < (vars->map->rows - 1))
    {
        j = 0;
        while (j < vars->map->cols)
        {
            tile_x = (j * TILE_SIZE) * 0.25;//MINIMAP_SCALE_FACTOR;
            tile_y = (i * TILE_SIZE) * 0.25;//MINIMAP_SCALE_FACTOR;
            printf("%c", vars->map->grid[i][j]);
            if (vars->map->grid[i][j] == '1')
                put_rectangle(&data, tile_x, tile_y, tile_x + TILE_SIZE, tile_y + TILE_SIZE, 0X0000FF00);
            j++;
        }
        printf("\n");
        i++;
    }
}
#include "cub3d.h"

int has_wall_at(double x, double y, t_vars *vars) //adicionar argumento com grid aka mapa
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
    //float tile_x;
    //float tile_y;

    //tile_x = vars->width / vars->map->cols;
    //tile_y = vars->height / vars->map->rows;
    if (x < 0 || x > vars->width || y < 0 || y > vars->height)
        return (TRUE);
    //map_grid_index_x = floor(x / tile_x);
    //map_grid_index_y = floor(y / tile_y);
    map_grid_index_x = floor(x / TILE_SIZE);
    map_grid_index_y = floor(y / TILE_SIZE);
 
    return (vars->map->grid[map_grid_index_y][map_grid_index_x] != 0);
}

void render_map(t_vars *vars, t_data data) //eventualmente mapa como argumento
{
    int     i;
    int     k;
    int     tile_x;
    int     tile_y;
    int     tile_color;

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

    //printf("\nAQUI\n");
    i = 0;
    while (i < vars->map->rows)
    {
        k = 0;
        while (k < vars->map->cols)
        {
            tile_x = (k * TILE_SIZE);// * MINIMAP_SCALE_FACTOR;
            tile_y = (i * TILE_SIZE);// * MINIMAP_SCALE_FACTOR;
            tile_color = vars->map->grid[i][k] == '1' ? 0X0000FF00 : 0X00FFFFFF;
            //printf("%c", vars->map->grid[i][k]);
            put_rectangle(&data, tile_x, tile_y, tile_x + TILE_SIZE, tile_y + TILE_SIZE, tile_color);
            put_rectangle(&data, tile_x, tile_y, tile_x, tile_y + TILE_SIZE, 0X00000000);
            put_rectangle(&data, tile_x, tile_y, tile_x + TILE_SIZE, tile_y, 0X00000000);
            k++;
        }
        //printf("\n");
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
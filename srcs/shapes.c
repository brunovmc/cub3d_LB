#include "../include/cub3d.h"

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
    while (y <= size_y)
    {
        x = init_x;
        while (x <= size_x)
        {
            my_pixel_put(data, x, y, color);
            x++;
        }
        y++;
    }
}

void put_rays_G(t_data *data, t_vars *vars, double x, double y, int color)
{
    //double rayAngle = ((vars->player->dir) * 3.14) / 180 - 30 * 3.14 / 180;
    double rayAngle = vars->player->dir_rad - 30 * 3.14 / 180;

    //double rayAngle = ((vars->player->dir) * 3.14) / 180;


    //COLOCAR NO .h posteriormente
    int WALL_STRIP_WIDTH = 10;
    double NUM_RAYS = WINDOW_WIDTH / WALL_STRIP_WIDTH;

    int i = 0;
    while (i < NUM_RAYS)
    //while (i < 1)
    {
        //if (i % 2 != 0)
        put_line_G(data, vars, vars->pos->x, vars->pos->y, rayAngle, 0x00ff0000);
        //else
        //put_line(data, vars, vars->pos->x, vars->pos->y, 100, 0x0000ff00);

        //rayAngle += 60 / NUM_RAYS;
        rayAngle += 3.14 / 180;
        i++;
    }
}

double distancebetweenpoints(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}

void put_line_G(t_data *data, t_vars *vars, double x, double y, double dir, int color)
{
    int i;
    int size = 0; //tamanho do raio
    double xintercept = 0;
    double yintercept = 0;
    double ystep = 0;
    double xstep = 0;
    //int step;
    int israyfacingdown = 0;
    int israyfacingup = 0;
    int israyfacingright = 0;
    int israyfacingleft = 0;

  

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

    //função pra determinar a primeira intersecção horizontal

    israyfacingdown = (dir > 0 && dir < 3.14); //? 1 : 0;
    israyfacingup = !israyfacingdown;

    israyfacingright = (dir < 0.5 * 3.14 || dir > 1.5 * 3.14);// ? 1 : 0;
    israyfacingleft = !israyfacingright;

    yintercept = floor(y / TILE_SIZE) * TILE_SIZE;
    yintercept += israyfacingdown ? TILE_SIZE : 0;
    xintercept = x  + (yintercept - y)/tan(dir);
    //printf("A xintercept: %f - yintercept: %f\n", xintercept, yintercept);


    ystep = TILE_SIZE;
    ystep *= israyfacingup ? -1 : 1;

    xstep = TILE_SIZE/tan(dir);
    xstep *= (israyfacingleft && xstep > 0) ? -1 : 1;
    xstep *= (israyfacingright && xstep < 0) ? -1 : 1;

    //printf("# xstep: %f - ystep: %f\n", xstep, ystep);


    //size = sqrt((x - xintercept) * (x - xintercept) + (y - yintercept) * (y - yintercept));

    /////

    int foundhorzwallhit = 0;
    double horzwallhitx = 0;
    double horzwallhity = 0;
    double nexthorztouchx = xintercept;
    double nexthorztouchy = yintercept;

    if (israyfacingup)
        nexthorztouchy--;
    
    //printf("A nexthrxtouchx: %f - nexthrztouchy: %f\n", nexthorztouchx, nexthorztouchy);
    while (nexthorztouchx >= 0 && nexthorztouchx <= WINDOW_WIDTH && nexthorztouchy >= 0 && nexthorztouchy <= WINDOW_HEIGHT && !foundhorzwallhit)
    {
        if (iscolision2(nexthorztouchx, nexthorztouchy) == 1)
        {
            foundhorzwallhit = 1;
            horzwallhitx = nexthorztouchx;
            horzwallhity = nexthorztouchy;
            //printf("B wallhitx: %f - wallhity: %f\n", wallhitx, wallhity);

            
            //size = sqrt((x - horzwallhitx) * (x - horzwallhitx) + (y - horzwallhity) * (y - horzwallhity));
            //i = 0;
            //while (i < size)
            //{
            //    my_pixel_put(data, (x + cos(dir) * i), (y + sin(dir) * i), color);
            //    i++;
            //}
            //break;
        }
        else
        {
            nexthorztouchx += xstep;
            nexthorztouchy += ystep;
            //printf("C nexthrxtouchx: %f - nexthrztouchy: %f\n\n", nexthorztouchx, nexthorztouchy);

        }
        
    }

    // intersecção com a vertical

    int     foundvertwallhit = 0;
    double  vertwallhitx = 0;
    double  vertwallhity = 0;

    xintercept = floor(x / TILE_SIZE) * TILE_SIZE;
    xintercept += israyfacingright ? TILE_SIZE : 0;

    yintercept = y + (xintercept - x) * tan(dir);

    xstep = TILE_SIZE;
    xstep *= israyfacingleft ? -1 : 1;

    ystep = TILE_SIZE * tan(dir);
    ystep *= (israyfacingup && ystep > 0) ? -1 : 1;
    ystep *= (israyfacingdown && ystep < 0) ? -1 : 1;

    double nextverttouchx = xintercept;
    double nextverttouchy = yintercept;

    while (nextverttouchx >= 0 && nextverttouchx <= WINDOW_WIDTH && nextverttouchy >= 0 && nextverttouchy <= WINDOW_HEIGHT)
    {
        if (iscolision2(nextverttouchx - (israyfacingleft ? 1 : 0), nextverttouchy))
        {
            foundvertwallhit = 1;
            vertwallhitx = nextverttouchx;
            vertwallhity = nextverttouchy;
            break;
        }
        else
        {
            nextverttouchx += xstep;
            nextverttouchy += ystep;
        }
    }

    double horzhitdistance = (foundhorzwallhit) ? distancebetweenpoints(x, y, horzwallhitx, horzwallhity) : 2000000000;
    double verthitdistance = (foundvertwallhit) ? distancebetweenpoints(x, y, vertwallhitx, vertwallhity) : 2000000000;
    
    double wallhitx = (horzhitdistance < verthitdistance) ? horzwallhitx : vertwallhitx;
    double wallhity = (horzhitdistance < verthitdistance) ? horzwallhity : vertwallhity;
    double distance = (horzhitdistance < verthitdistance) ? horzhitdistance : verthitdistance;
    int washitvertical = (verthitdistance < horzhitdistance);

    //pode ser uma função pra plotar uma linha
    //size = sqrt((x - wallhitx) * (x - wallhitx) + (y - wallhity) * (y - wallhity));

    i = 0;
    while (i < distance)
    {
        my_pixel_put(data, (x + cos(dir) * i), (y + sin(dir) * i), color);
       i++;
    }
}

void put_line(t_data *data, t_vars *vars, double x, double y, int size, int color)
{
    //double dir;
    int i;
    int dist;

    i = 0;
    vars->player->dir_rad = (vars->player->dir * 3.14) / 180;
    dist = size;
    while (i < dist)
    {

        vars->pos->new_x = (dist - i) * cos(vars->player->dir_rad);
        vars->pos->new_y = (dist - i) * sin(vars->player->dir_rad);

        // printf("dir = %f\n", vars->player->dir);
        // printf("vars->pos->x/TS = %f\n", x / TILE_SIZE);
        // printf("vars->pos->y/TS = %f\n", y / TILE_SIZE);

        my_pixel_put(data, (x + vars->pos->new_x), (y + vars->pos->new_y), color);
        i++;
    }
}

void put_circle(t_data *data, int a, int b, int size, int color)
{
    int x;
    int y;

    x = 0;
    while (x <= (a + size))
    {
        y = 0;
        while (y <= (b + size))
        {
            if ((x - a) * (x - a) + (y - b) * (y - b) <= size * size)
                my_pixel_put(data, x, y, color);
            y++;
        }
        x++;
    }
}

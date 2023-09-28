#ifndef PHYSICH
#define PHYSICH

#include "graphics/graphics.h"
#include "view.h"
#include "snake.h"
#include "map.h"

BOOL check_collide_map(Window window, POINT point, char map[MAP_SIZE][MAP_SIZE]);
BOOL check_collide_snake(Window window, POINT point, Snake* snake);
BOOL check_collide(Window window, POINT point, Snake* snake, char map[MAP_SIZE][MAP_SIZE]);
BOOL check_collide_points(POINT a, POINT b);

#endif 

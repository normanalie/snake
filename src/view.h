#ifndef VIEWH
#define VIEWH

#include <stdio.h>
#include "graphics/graphics.h"
#include "map.h"

#define ZOOMFACTOR 10


typedef enum CellType{
	HEAD,
	BODY,
	WALL,
	FRUIT,
	BG 
} CellType;

typedef struct Window{
	int width;
	int height;
	int game_width;
	int game_height;
} Window;

Window* view_init(int w);
void view_draw(Window window, POINT point, CellType type);
void view_erase(Window window);
void view_score(Window window, int score);

#endif

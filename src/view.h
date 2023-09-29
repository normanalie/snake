#ifndef VIEWH
#define VIEWH

#include <stdio.h>
#include "../lib/graphics/graphics.h"
#include "map.h"

#define ZOOMFACTOR 10


typedef enum CellType{
	HEAD,
	BODY,
	WALL,
	FRUIT,
	GOLDFRUIT,
	PARTICLES,
	BG 
} CellType;

typedef struct Window{
	int width;
	int height;
	int game_width;
	int game_height;
	int frame_time;
} Window;

Window* view_init(int w, int frameTime);
void view_draw(Window window, POINT point, CellType type);
void view_erase(Window window);
void view_score(Window window, int score);
void view_title_screen(Window window);
void view_game_over(Window window, int score);
#endif

#ifndef VIEWH
#define VIEWH

#include <stdio.h>
#include "graphics/graphics.h"

#define ZOOMFACTOR 10

typedef enum CellType{
	HEAD,
	BODY,
	WALL,
	FRUIT,
	BG 
} CellType;

void view_init(int w, int h);
void draw(POINT point, CellType type);
void view_erase();
void view_score(int score);

#endif // !DEBUG

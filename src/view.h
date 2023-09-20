#ifndef VIEWH
#define VIEWH

#include <stdio.h>
#include "graphics/graphics.h"

#define ZOOMFACTOR 10

typedef enum CellType{
	HEAD,
	BODY,
	WALL,
	BG 
} CellType;

void view_init(int w, int h);
void draw(POINT point, CellType type);
void update();


#endif // !DEBUG

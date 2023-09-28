#ifndef FRUITH
#define FRUITH

#include "graphics/graphics.h"

typedef struct Fruit {
	POINT pos;
	POINT oldPos;
} Fruit;

Fruit* fruit_generate(int windowW, int windowH, int zoomfactor);

#endif // !DEBUG

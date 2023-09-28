#ifndef FRUITH
#define FRUITH

#include "graphics/graphics.h"
#include "view.h"

typedef struct Fruit {
	POINT pos;
	POINT oldPos;
  CellType type;	
} Fruit;

Fruit* fruit_init();

#endif // !DEBUG

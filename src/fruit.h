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
BOOL fruit_have_pos(Fruit fruit);  
BOOL fruit_have_old_pos(Fruit fruit); 
BOOL fruit_set_type(Fruit* fruit, CellType type);  // Return TRUE if type is valid and set else return FALSE.
void fruit_set_pos(Fruit* fruit, POINT pos);

#endif // !DEBUG

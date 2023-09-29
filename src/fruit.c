#include "fruit.h"
#include "graphics/graphics.h"
#include "view.h"

Fruit* fruit_init(){
	Fruit *fruit;
	fruit = (Fruit*)malloc(sizeof(Fruit));
	fruit->pos.x = -1; 
	fruit->pos.y = -1;
	fruit->oldPos.x = -1;
	fruit->oldPos.y = -1;
	fruit->type = FRUIT;
	return fruit;

}

BOOL fruit_have_pos(Fruit fruit){
	return (fruit.pos.x >= 0) && (fruit.pos.y >= 0);
}

BOOL fruit_have_old_pos(Fruit fruit){
	return (fruit.oldPos.x >= 0) && (fruit.oldPos.y >= 0);
}

BOOL fruit_set_type(Fruit* fruit, CellType type){
	if(type == FRUIT || type == GOLDFRUIT){
		fruit->type = type;
		return TRUE;
	}
	return FALSE;
}

void fruit_set_pos(Fruit* fruit, POINT pos){
	fruit->oldPos = fruit->pos;
	fruit->pos.x = pos.x;
	fruit->pos.y = pos.y;
	return;
}

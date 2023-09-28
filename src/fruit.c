#include "fruit.h"
#include "graphics/graphics.h"

Fruit* fruit_init(){
	Fruit *fruit;
	fruit = (Fruit*)malloc(sizeof(Fruit));
	fruit->pos.x = -1; 
	fruit->pos.y = -1;
	fruit->oldPos.x = -1;
	fruit->oldPos.y = -1;
	return fruit;

}


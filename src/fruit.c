#include "fruit.h"
#include "graphics/graphics.h"

Fruit* fruit_generate(int windowW, int windowH, int zoomfactor){
	Fruit *fruit;
	fruit = (Fruit*)malloc(sizeof(Fruit));
	fruit->pos.x = alea_int(windowW-zoomfactor) + zoomfactor;
	fruit->pos.y = alea_int(windowH-zoomfactor) + zoomfactor;
	return fruit;
}

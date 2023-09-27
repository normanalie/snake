#ifndef SNAKE
#define SNAKE

#include <stdio.h>
#include "directions.h"
#include <stdlib.h>

typedef struct Snake Snake;
typedef struct SnakeElem SnakeElem;

struct SnakeElem {
	int x;
	int y;
	SnakeElem *next;
};

struct Snake {
	direction dir;
	SnakeElem *head;
};


Snake* snake_init(int x, int y, direction dir);
void snake_free(Snake *snake);
void snake_grow(Snake *snake); 
void snake_move(Snake *snake);
SnakeElem* snake_get_tail(Snake *snake);
SnakeElem* snake_get_head(Snake *snake);

#endif

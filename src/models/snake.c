#include "snake.h"

Snake* snake_init(int x, int y, direction dir){
  Snake *snake;
  snake = (Snake*) malloc(sizeof(Snake));

  SnakeElem *head;
  head = (SnakeElem*) malloc(sizeof(SnakeElem));
  head->x = x;
  head->y = y;
  head->next = NULL;

  snake->head = head;
  snake->dir = dir;

  return snake;
}

void snake_grow(Snake *snake){
  SnakeElem *new;
  new = (SnakeElem*) malloc(sizeof(SnakeElem));

  switch (snake->dir) {
    case UP:
      new->x = snake->head->x;
      new->y = snake->head->y+1;
      break;
    case DOWN:
      new->x = snake->head->x;
      new->y = snake->head->y-1;
      break;
    case LEFT:
      new->x = snake->head->x-1;
      new->y = snake->head->y;
      break;
    case RIGHT:
      new->x = snake->head->x+1;
      new->y = snake->head->y;
      break;
  }

  new->next = snake->head;
  snake->head = new;

  return;
}

void snake_free(Snake *snake){
  SnakeElem *toDelete;
  while(snake->head != NULL){
    toDelete = snake->head;
    snake->head = snake->head->next;
    free(toDelete);
  }
  free(snake);

  return;
}

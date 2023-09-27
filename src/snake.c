#include "snake.h"
#include "graphics/graphics.h"
#include "view.h"

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
      new->y = snake->head->y+ZOOMFACTOR;
      break;
    case DOWN:
      new->x = snake->head->x;
      new->y = snake->head->y-ZOOMFACTOR;
      break;
    case LEFT:
      new->x = snake->head->x-ZOOMFACTOR;
      new->y = snake->head->y;
      break;
    case RIGHT:
      new->x = snake->head->x+ZOOMFACTOR;
      new->y = snake->head->y;
      break;
    case NO_DIR:
      return;
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

void snake_move(Snake *snake){
  int prevX = snake->head->x;
  int prevY = snake->head->y;
  int SPEED = 2;
  switch (snake->dir) {
    case UP:
      snake->head->y += ZOOMFACTOR*SPEED;
      break;
    case DOWN:
      snake->head->y -= ZOOMFACTOR*SPEED;
      break;
    case LEFT:
      snake->head->x -= ZOOMFACTOR*SPEED;
      break;
    case RIGHT:
      snake->head->x += ZOOMFACTOR*SPEED;
      break;
    case NO_DIR:
      return;
      break;
  }
  if(snake->head->x < 0) snake->head->x = WIDTH;
  if(snake->head->x > WIDTH) snake->head->x = 0;
  if(snake->head->y < 0) snake->head->y = HEIGHT;
  if(snake->head->y > HEIGHT) snake->head->y = 0;

  SnakeElem *curr = snake->head->next;
  int tmp;
  while(curr != NULL){
    tmp = curr->x;
    curr->x = prevX;
    prevX = tmp;
    tmp = curr->y;
    curr->y = prevY;
    prevY = tmp;
    curr = curr->next;
  }
  return;
}

SnakeElem* snake_get_tail(Snake* snake){
  SnakeElem *elem = snake->head;
  while(elem->next != NULL){
    elem = elem->next;
  }
  return elem;
}

SnakeElem* snake_get_head(Snake *snake){
  return snake->head;
}

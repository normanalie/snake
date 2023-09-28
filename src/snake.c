#include "snake.h"
#include "graphics/graphics.h"
#include "view.h"
#include <stdlib.h>

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
  snake->speed = 2;
  snake->oldTailPos = (POINT*) malloc(sizeof(POINT));
  snake->oldTailPos->x = x;
  snake->oldTailPos->y = y;

  return snake;
}

void snake_grow(Snake *snake){
  SnakeElem *new;
  new = (SnakeElem*) malloc(sizeof(SnakeElem));

  switch (snake->dir) {
    case UP:
      new->x = snake->head->x;
      new->y = snake->head->y+ZOOMFACTOR*snake->speed;
      break;
    case DOWN:
      new->x = snake->head->x;
      new->y = snake->head->y-ZOOMFACTOR*snake->speed;
      break;
    case LEFT:
      new->x = snake->head->x-ZOOMFACTOR*snake->speed;
      new->y = snake->head->y;
      break;
    case RIGHT:
      new->x = snake->head->x+ZOOMFACTOR*snake->speed;
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

void snake_move_propagate(Snake *snake, int prevX, int prevY){
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
  snake->oldTailPos->x = prevX;
  snake->oldTailPos->y = prevY;
  return;
}

void snake_move(Snake *snake, int maxX, int maxY){
  int prevX = snake->head->x;
  int prevY = snake->head->y;
  int SPEED = snake->speed;
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
  if(snake->head->x < 0) snake->head->x = maxX;
  if(snake->head->x > maxX) snake->head->x = 0;
  if(snake->head->y < 0) snake->head->y = maxY;
  if(snake->head->y > maxY) snake->head->y = 0;

  snake_move_propagate(snake, prevX, prevY);
  
  return;
}

BOOL snake_eat_self(Snake *snake){
  int negativeMargin = snake->speed;
  POINT snakeHead;
  snakeHead.x = snake->head->x;
  snakeHead.y = snake->head->y;
  SnakeElem *elem = snake->head->next;
  while(elem != NULL){
    POINT elemPoint;
    elemPoint.x = elem->x;
    elemPoint.y = elem->y;
    if(distance(elemPoint, snakeHead) < ZOOMFACTOR-negativeMargin) return TRUE;
    elem = elem->next;
  }
  return FALSE;
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

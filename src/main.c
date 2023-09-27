#include <stdio.h>
#include "fruit.h"
#include "graphics/graphics.h"
#include "snake.h"
#include "fruit.h"
#include "view.h"
#include "config.h"


direction get_direction();
void update(Snake* snake, Fruit* fruit, int* score);
void refresh(Snake* snake, Fruit* fruit, int score);

int main(){
  Snake *snake;
  snake = snake_init(100, 100, RIGHT);
  snake_grow(snake);
  snake_grow(snake);
  view_init(WIDTH, HEIGHT);

  Fruit *fruit; 
  fruit = fruit_generate(WIDTH, HEIGHT, ZOOMFACTOR);
  draw(fruit->pos, FRUIT);

  int score = 0;

  while(1){
    update(snake, fruit, &score);
    refresh(snake, fruit, score);
  }
  exit(0);
}

void update(Snake* snake, Fruit* fruit, int *score){
  attendre(20);
  snake_move(snake);

  direction newDir = get_direction();
  switch (newDir) {
    case UP:
      if(snake->dir != DOWN) snake->dir = newDir;
      break;
    case DOWN:
      if(snake->dir != UP) snake->dir = newDir;
      break;
    case RIGHT:
      if(snake->dir != LEFT) snake->dir = newDir;
      break;
    case LEFT:
      if(snake->dir != RIGHT) snake->dir = newDir;
      break;
    case NO_DIR:
      break;
  }

  POINT snakeHead;
  snakeHead.x = snake_get_head(snake)->x;
  snakeHead.y = snake_get_head(snake)->y;
  if(distance(snakeHead, fruit->pos) < ZOOMFACTOR){
    fruit->pos = fruit_generate(WIDTH, HEIGHT, ZOOMFACTOR)->pos;
    *score = *score+1;
  }
}

void refresh(Snake* snake, Fruit* fruit, int score){
  view_erase();
 
  POINT point;
  SnakeElem *body = snake_get_head(snake);
  while(body != NULL){
    point.x = body->x;
    point.y = body->y;
    draw(point, BODY);
    body = body->next;
  }

  draw(fruit->pos, FRUIT);

  view_score(score);
}


direction get_direction(){
  POINT arrow;
  arrow.x = 0;
  arrow.y = 0;

  arrow = get_arrow();
  if(arrow.x > 0) return RIGHT;
  if(arrow.x < 0) return LEFT;
  if(arrow.y > 0) return UP;
  if(arrow.y < 0) return DOWN;
  return NO_DIR;
}

#include <stdio.h>
#include "graphics/graphics.h"
#include "models/snake.h"
#include "view.h"

direction get_direction();

int main(){
  Snake *snake;
  snake = snake_init(100, 100, RIGHT);
  snake_grow(snake);
  snake_grow(snake);
  view_init(800, 450);

  POINT center;
  while(1){
    SnakeElem *body = snake_get_head(snake);
    while(body != NULL){ 
      center.x = body->x;
      center.y = body->y;
      draw(center, BODY);
      body = body->next;
    }
    attendre(10);
    SnakeElem *oldtail = snake_get_tail(snake);
    snake_move(snake);
    snake_grow(snake);
    center.x = oldtail->x;
    center.y = oldtail->y;
    draw(center, BG);
    direction newDir = get_direction();
    if(newDir) snake->dir = newDir;
  }
  exit(0);
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

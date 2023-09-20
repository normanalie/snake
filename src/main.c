#include <stdio.h>
#include "graphics/graphics.h"
#include "models/snake.h"
#include "view.h"

int main(){
  Snake *snake;
  snake = snake_init(100, 100, RIGHT);
  snake_grow(snake);
  snake_grow(snake);
  view_init(800, 450);

  POINT center;
  POINT arrow;
  arrow.x = 0;
  arrow.y = 0;
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
    center.x = oldtail->x;
    center.y = oldtail->y;
    draw(center, BG);

    arrow = get_arrow();
    if(arrow.x > 0) snake->dir = RIGHT;
    if(arrow.x < 0) snake->dir = LEFT;
    if(arrow.y > 0) snake->dir = UP;
    if(arrow.y < 0) snake->dir = DOWN;
  }
  exit(0);
}


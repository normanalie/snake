#include <stdio.h>
#include "graphics/graphics.h"
#include "models/snake.h"

int main(){
  Snake *snake;
  snake = snake_init(10, 10, RIGHT);
  snake_grow(snake);
  snake_grow(snake);
  init_graphics(850, 480);

  while(1){
    SnakeElem *body = snake->head;
    while(body != NULL){
      POINT center;
      center.x = body->x*10;
      center.y = body->y*10;
      draw_fill_circle(center, 10, blanc);
      body = body->next;
    }
    attendre(200);
    snake_move(snake);
    printf("%d %d\n", snake->head->x, snake->head->y);
  }
  exit(0);
}


#include <stdio.h>
#include "graphics/graphics.h"
#include "models/snake.h"

int main(){
  Snake *snake;
  snake = snake_init(10, 10, RIGHT);
  init_graphics(480, 850);
  wait_escape();
  exit(0);
}

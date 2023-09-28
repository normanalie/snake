#include <stdio.h>
#include "fruit.h"
#include "graphics/graphics.h"
#include "snake.h"
#include "fruit.h"
#include "view.h"
#include "config.h"
#include "map.h"

char map[MAP_SIZE][MAP_SIZE] = MAP;

direction get_direction();
BOOL check_collide(Window window, POINT point, char map[MAP_SIZE][MAP_SIZE]);
BOOL update(Window window, Snake* snake, Fruit* fruit, int* score);
void refresh(Window window, Snake* snake, Fruit* fruit, int score);

int main(int argc, char *argv[]){
  int width = DEFAULT_SIZE;
  if(argc == 2){
    width = atoi(argv[1]);
  }
  Window* window;
  window = view_init(width);
  
  int score = 0;

  Snake *snake;
  snake = snake_init(100, 100, RIGHT);
  snake_grow(snake);
  snake_grow(snake);

  Fruit *fruit;
  do{
    fruit = fruit_generate(window->game_width, window->game_height, ZOOMFACTOR);
  }while(check_collide(*window, fruit->pos, map));
  fruit->oldPos.x = -1;
  fruit->oldPos.y = -1;
 
  BOOL inGame = TRUE;
  int dt = 0;
  while(inGame){
    attendre(200-dt);
    chrono_start();
    inGame = update(*window, snake, fruit, &score);
    refresh(*window, snake, fruit, score); 
    dt = (int)(chrono_val()*1000);
  }
  exit(0);
}

BOOL check_collide(Window window, POINT point, char map[MAP_SIZE][MAP_SIZE]){
  int negativeMargin = 10;
  for(int i=0; i<MAP_SIZE; i++){
    for(int j=0; j<MAP_SIZE; j++){
      if(map[i][j] == 'x'){
        POINT botLeft;
        botLeft.x = j*(window.game_width/MAP_SIZE);
        botLeft.y = i*(window.game_height/MAP_SIZE);
        POINT center;
        center.x = (botLeft.x+(window.game_width/MAP_SIZE)/2);
        center.y = (botLeft.y+(window.game_height/MAP_SIZE)/2);
        if(distance(point, center) < window.game_width/MAP_SIZE+ZOOMFACTOR/2-negativeMargin) return TRUE;
      }
    }
  }
  return FALSE;
}

BOOL update(Window window, Snake* snake, Fruit* fruit, int *score){
  snake_move(snake, window.game_width, window.game_height);

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
  if(distance(snakeHead, fruit->pos) < (ZOOMFACTOR*2)){
    fruit->oldPos = fruit->pos;
    do{
      fruit->pos = fruit_generate(window.game_width, window.game_height, ZOOMFACTOR)->pos;
    }while(check_collide(window, fruit->pos, map));
    *score = *score+1;
    snake_grow(snake);
  }

  if(check_collide(window, snakeHead, map)){
    return FALSE;
  }
  return TRUE;
}

void refresh(Window window, Snake* snake, Fruit* fruit, int score){
  draw(window, fruit->oldPos, BG);

  for(int i=0; i<MAP_SIZE; i++){
    for(int j=0; j<MAP_SIZE; j++){
      if(map[i][j] == 'x'){
        POINT wall;
        wall.x = j*(window.game_width/MAP_SIZE);
        wall.y = i*(window.game_height/MAP_SIZE);
        draw(window, wall, WALL);
      }
    }
  }

 
  POINT point;
  SnakeElem *body = snake_get_head(snake);
  while(body != NULL){
    point.x = body->x;
    point.y = body->y;
    draw(window, point, BODY);
    body = body->next;
  }
  draw(window, *snake->oldTailPos, BG);

  draw(window, fruit->pos, FRUIT);

  view_score(window, score);
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

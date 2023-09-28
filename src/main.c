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
BOOL check_collide_map(Window window, POINT point, char map[MAP_SIZE][MAP_SIZE]);
BOOL check_collide_snake(Window window, POINT point, Snake* snake);
BOOL check_collide(Window window, POINT point, Snake* snake, char map[MAP_SIZE][MAP_SIZE]);
BOOL check_collide_points(POINT a, POINT b); 
POINT* find_empty(Window window, Snake* snake, char map[MAP_SIZE][MAP_SIZE]);
BOOL update(Window window, Snake* snake, Fruit* fruit, int* score);
void refresh(Window window, Snake* snake, Fruit* fruit, int score);
void draw_map(Window window, char map[MAP_SIZE][MAP_SIZE]);

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
  fruit = fruit_init();
  fruit->pos = *find_empty(*window, snake, map);
 
  draw_map(*window, map);

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

BOOL check_collide_map(Window window, POINT point, char map[MAP_SIZE][MAP_SIZE]){
  int negativeMargin = 9;
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

BOOL check_collide_snake(Window window, POINT point, Snake* snake){
  SnakeElem* elem = snake_get_head(snake);
  while(elem->next != NULL){
    POINT elemPoint;
    elemPoint.x = elem->x;
    elemPoint.y = elem->y;
    if(check_collide_points(point, elemPoint)) return TRUE;
    elem = elem->next;
  }
  return FALSE;
}

BOOL check_collide(Window window, POINT point, Snake* snake, char map[MAP_SIZE][MAP_SIZE]){
  if(check_collide_map(window, point, map)) return TRUE;
  if(check_collide_snake(window, point, snake)) return TRUE;
  return FALSE;
}

BOOL check_collide_points(POINT a, POINT b){
  if(distance(a, b) < ZOOMFACTOR*2) return TRUE;
  return FALSE;
}

POINT* find_empty(Window window, Snake* snake, char map[MAP_SIZE][MAP_SIZE]){
  POINT* empty = (POINT*) malloc(sizeof(POINT));
  do{
    empty->x = alea_int(window.game_width);
    empty->y = alea_int(window.game_height); 
  }while(check_collide(window, *empty, snake, map));
  return empty;
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
  if(check_collide_points(snakeHead, fruit->pos)){
    fruit->oldPos = fruit->pos;
    fruit->pos = *find_empty(window, snake, map);
    *score = *score+1;
    snake_grow(snake);
  }

  if(check_collide_map(window, snakeHead, map))return FALSE;
  if(snake_eat_self(snake)) return FALSE;
  return TRUE;
}

void refresh(Window window, Snake* snake, Fruit* fruit, int score){
  if(fruit->oldPos.x >= 0 && fruit->oldPos.y >= 0){
    view_draw(window, fruit->oldPos, BG); 
  }
  if(fruit->pos.x >= 0 && fruit->pos.y >= 0){
    view_draw(window, fruit->pos, FRUIT);
  }
 
  POINT point;
  SnakeElem *head = snake_get_head(snake);
  point.x = head->x;
  point.y = head->y;
  view_draw(window, point, HEAD);

  SnakeElem *body = head->next;
  while(body != NULL){
    point.x = body->x;
    point.y = body->y;
    view_draw(window, point, BODY);
    body = body->next;
  }
  view_draw(window, *snake->oldTailPos, BG);

  view_score(window, score);
}

void draw_map(Window window, char map[MAP_SIZE][MAP_SIZE]){
  for(int i=0; i<MAP_SIZE; i++){
    for(int j=0; j<MAP_SIZE; j++){
      if(map[i][j] == 'x'){
        POINT wall;
        wall.x = j*(window.game_width/MAP_SIZE);
        wall.y = i*(window.game_height/MAP_SIZE);
        view_draw(window, wall, WALL);
      }
    }
  }
  return;
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

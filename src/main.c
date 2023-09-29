#include <stdio.h>
#include "fruit.h"
#include "graphics/graphics.h"
#include "snake.h"
#include "fruit.h"
#include "view.h"
#include "config.h"
#include "map.h"
#include "physic.h"

char map[MAP_SIZE][MAP_SIZE] = MAP;

direction get_direction(); 
POINT* find_empty(Window window, Snake* snake, char map[MAP_SIZE][MAP_SIZE]);
BOOL update(Window window, Snake* snake, Fruit* fruit, int* score, int* boost);  // Return TRUE while game is running, FALSE if lost.
void refresh(Window window, Snake* snake, Fruit* fruit, int score, int boost, char map[MAP_SIZE][MAP_SIZE]);
void draw_map(Window window, char map[MAP_SIZE][MAP_SIZE]);
void decrease_boost(int* boost); 

int main(int argc, char *argv[]){
  int width = DEFAULT_SIZE;
  if(argc == 2){
    width = atoi(argv[1]);
  }
  Window* window;
  window = view_init(width, DEFAULT_FRAME_TIME);

  view_title_screen(*window);
  wait_clic();

  int score = 0;

  Snake *snake;
  snake = snake_init(100, 100, RIGHT);
  snake_grow(snake);
  snake_grow(snake);

  Fruit *fruit;
  fruit = fruit_init();
  fruit->pos = *find_empty(*window, snake, map);
 
  view_erase(*window);
  draw_map(*window, map);
  
  BOOL inGame = TRUE;
  int boost = 0;
  int dt = 0;
  while(inGame){
    attendre(window->frame_time-dt-boost);
    chrono_start();
    inGame = update(*window, snake, fruit, &score, &boost);
    refresh(*window, snake, fruit, score, boost, map); 
    dt = (int)(chrono_val()*1000);
  } 

  view_game_over(*window, score);
  wait_escape();

  snake_free(snake);
  free(fruit);
  free(window);
  exit(0);
}

POINT* find_empty(Window window, Snake* snake, char map[MAP_SIZE][MAP_SIZE]){
  POINT* empty = (POINT*) malloc(sizeof(POINT));
  do{
    empty->x = alea_int(window.game_width);
    empty->y = alea_int(window.game_height); 
  }while(check_collide(window, *empty, snake, map));
  return empty;
}

BOOL update(Window window, Snake* snake, Fruit* fruit, int *score, int *boost){
  decrease_boost(boost);
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

  POINT snakeHead = *snake_to_point(*snake_get_head(snake));
  if(check_collide_points(snakeHead, fruit->pos)){ 
    if(fruit->type == GOLDFRUIT){
      *score = *score + 2;
      snake_grow(snake);
      snake_grow(snake);
      *boost = DEFAULT_FRAME_TIME/3;
    }else{
      *score = *score+1;
      snake_grow(snake);
    }

    fruit_set_pos(fruit, *find_empty(window, snake, map));
    if(alea_int(5)){
      fruit_set_type(fruit, FRUIT);
    }else{
      fruit_set_type(fruit, GOLDFRUIT);
    }
  }

  if(check_collide_map(window, snakeHead, map))return FALSE;
  if(snake_eat_self(snake)) return FALSE;
  return TRUE;
}

void refresh(Window window, Snake* snake, Fruit* fruit, int score, int boost, char map[MAP_SIZE][MAP_SIZE]){
  if(fruit_have_old_pos(*fruit)){
    view_draw(window, fruit->oldPos, BG); 
  }
  if(fruit_have_pos(*fruit)){
    view_draw(window, fruit->pos, fruit->type);
  }
 
  POINT head = *snake_to_point(*snake_get_head(snake));
  view_draw(window, head, HEAD);

  SnakeElem *body = snake_get_head(snake)->next;
  POINT point;
  while(body != NULL){
    point = *snake_to_point(*body);
    if(boost && body->next == NULL){
      view_draw(window, point, BG);
      view_draw(window, point, PARTICLES);
    }else{
      view_draw(window, point, BODY);
    }
    body = body->next;
  }
  view_draw(window, *snake->oldTailPos, BG); 

  view_score(window, score);
  return;
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

void decrease_boost(int *boost){
  int boostDecrease = 3;
  if(*boost){
    *boost -= boostDecrease;
  }
  if(*boost < 0){
    *boost = 0; 
  }
  return;
}

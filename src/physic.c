#include "physic.h"

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

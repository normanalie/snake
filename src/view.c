#include "view.h"
#include "graphics/graphics.h"
#include "map.h"
#include <stdlib.h>

Window* view_init(int w){
  int h = w+50; 

  Window* window = (Window*) malloc(sizeof(Window));
  window->width = w;
  window->height = h;
  window->game_width = w;
  window->game_height = w;

  init_graphics(window->width, window->height);
  return window;
}

void view_draw_wall(Window window, POINT point){
  POINT topRight, botLeft;
  topRight.x = point.x+(window.game_width/MAP_SIZE);
  topRight.y = point.y+(window.game_height/MAP_SIZE);
  botLeft.x = point.x;
  botLeft.y = point.y;
  draw_fill_rectangle(topRight, botLeft, blanc);
  return;
}

void view_draw(Window window, POINT point, CellType type){ 
  switch (type) {
    case WALL:
      view_draw_wall(window, point);
      break;
    case HEAD:
      draw_fill_circle(point, ZOOMFACTOR, goldenrod);
      POINT eye;
      eye.x = point.x + ZOOMFACTOR/2;
      eye.y = point.y + ZOOMFACTOR/3;
      draw_fill_circle(eye, 3, black);
      break;
    case BODY:
      draw_fill_circle(point, ZOOMFACTOR, yellow);
      break;
    case FRUIT:
      draw_fill_circle(point, ZOOMFACTOR, red);
      break;
    case BG:
      draw_fill_circle(point, ZOOMFACTOR, black);
      break;
  }
  return;
}

void view_erase(Window window){
  POINT origin, end;
  origin.x = 0;
  origin.y = 0;
  end.x = window.width;
  end.y = window.height; 
  draw_fill_rectangle(origin, end, black);
  return;
}

void view_erase_score(Window window){
  POINT origin, end;
  origin.x = 0;
  origin.y = window.game_height;
  end.x = window.width;
  end.y = window.height;
  draw_fill_rectangle(origin, end, black);
  return;
}

void view_score(Window window, int score){
  view_erase_score(window);
  char scoreText[30];
  int fontSize = 20;
  POINT scoreTextOrigin;
  scoreTextOrigin.x = 10;
  scoreTextOrigin.y =  window.game_height+fontSize*2;
  sprintf(scoreText, "Score: %d", score);
  aff_pol(scoreText, fontSize, scoreTextOrigin, red);
  return;
}

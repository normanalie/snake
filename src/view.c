#include "view.h"
#include "graphics/graphics.h"

void view_init(int w, int h){
  init_graphics(w, h);
  return;
}

void draw_wall(POINT center){
  POINT topRight, botLeft;
  topRight.x = center.x + (ZOOMFACTOR/2);
  topRight.y = center.y + (ZOOMFACTOR/2);
  botLeft.x = center.x - (ZOOMFACTOR/2);
  botLeft.y = center.y - (ZOOMFACTOR/2);
  draw_fill_rectangle(topRight, botLeft, blanc);
  return;
}

void draw(POINT point, CellType type){ 
  switch (type) {
    case WALL:
      point.x = point.x*10;
      point.y = point.y*10;
      draw_wall(point);
      break;
    case HEAD:
      draw_fill_circle(point, ZOOMFACTOR, blanc);
      break;
    case BODY:
      draw_fill_circle(point, ZOOMFACTOR, jaune);
      break;
    case BG:
      draw_fill_circle(point, ZOOMFACTOR*2, black);
      break;
  }
  return;
}

void update(){
  synchro();
}

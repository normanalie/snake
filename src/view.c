#include "view.h"
#include "graphics/graphics.h"
#include "map.h"
#include <stdlib.h>

Window* view_init(int w, int frameTime){
  int h = w+50; 

  Window* window = (Window*) malloc(sizeof(Window));
  window->width = w;
  window->height = h;
  window->game_width = w;
  window->game_height = w;
  window->frame_time = frameTime;

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

void view_draw_apple(POINT point, COULEUR color){
  draw_fill_circle(point, ZOOMFACTOR, color);
  POINT leaf;
  leaf.x = point.x + 2;
  leaf.y = point.y + ZOOMFACTOR - 4;
  draw_fill_circle(leaf, 3, green);
  POINT bite;
  bite.x = point.x + ZOOMFACTOR;
  bite.y = point.y;
  draw_fill_circle(bite, ZOOMFACTOR-3, black);
  return;
}

void view_draw_particles(POINT point){
  POINT particles[3];
  for(int i=0; i<3; i++){
    int randX = alea_int(ZOOMFACTOR-3);
    int randY = alea_int(ZOOMFACTOR-3);
    if(alea_int(2)){
      particles[i].x = point.x + randX;
    } else {
      particles[i].x = point.x - randX;
    }
    if(alea_int(2)){
      particles[i].y = point.y + randY;
    } else {
      particles[i].y = point.y - randY;
    }
    draw_fill_circle(particles[i], 1, gold);
  }
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
      view_draw_apple(point, red);
      break;
    case GOLDFRUIT:
      view_draw_apple(point, gold);
      break;
    case PARTICLES:
      view_draw_particles(point);
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
  draw_fill_rectangle(origin, end, lightgrey);
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

void view_title_screen(Window window){
  POINT origin, end;
  origin.x = 0;
  origin.y = 0;
  end.x = window.width;
  end.y = window.height;
  draw_fill_rectangle(origin, end, lightgrey);

  POINT textOrigin;
  int fontSize = 40;
  textOrigin.x = window.width/2 - fontSize*2;
  textOrigin.y = window.height/2 + fontSize/2;
  aff_pol("SNAKE", fontSize, textOrigin, red);
  
  fontSize = 22;
  textOrigin.y -= fontSize*2;
  aff_pol("Clic to start...", fontSize, textOrigin, lightsalmon);
  return;
}

void view_game_over(Window window, int score){
  POINT origin, end;
  origin.x = 0;
  origin.y = 0;
  end.x = window.width;
  end.y = window.height;
  draw_fill_rectangle(origin, end, lightgrey);

  POINT textOrigin;
  int fontSize = 40;
  textOrigin.x = window.width/2 - fontSize*3;
  textOrigin.y = window.height/2 + fontSize/2;
  aff_pol("GAME OVER", fontSize, textOrigin, red);

  char scoreText[30];
  sprintf(scoreText, "Your score: %d", score);
  fontSize=22;
  textOrigin.x += fontSize*2;
  textOrigin.y -= fontSize*2;
  aff_pol(scoreText, fontSize, textOrigin, lightsalmon);
  return;
}

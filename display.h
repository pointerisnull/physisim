#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>
#include "object.h"

typedef struct {
	float x,y,z;
	float mousex, mousey;
  
  int mapscale;
  float zoom;
} Camera;

class Window {
  private:
    void drawpixel(float x,float y, int r, int g, int b);
    void drawcircle(float centreX, float centreY, float radius, int r, int g, int b);
    void drawline (int x, int y1, int y2, int r, int g, int b);
    void adjustCoords2D(float *x, float *y);
    void adjustMouseCoords(int *x, int *y);
    void drawmap();
    
    int width, height;
    int width2, height2;
    SDL_Window *win;
    SDL_Renderer *renderer;
    SDL_Event event;
    Camera cam;

  public:
    void clear();
    void draw(Object obj);
    void update();
    void check_updates();
    void kill();
    
    Window();
    Window(char *title, int w, int h);

    int running;
};

#endif

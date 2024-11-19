#ifndef DISPLAY_H
#define DISPLAY_H

#include <SDL2/SDL.h>

typedef struct {
	float x,y,z;
	float mousex, mousey;
  
  int mapscale;
  float zoom;
} Camera;

class Window {
  private:
    void drawpixel(float x,float y, int r, int g, int b);
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
    void create(char *title, int w, int h);
    void draw();
    void check_updates();
    void kill();

    int running;
};

#endif

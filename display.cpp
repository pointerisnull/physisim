#include <SDL2/SDL.h>
#include <glad/glad.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "display.h"

void Window::adjustCoords2D(float *x, float *y) {
  *x = (*x-cam.x)*cam.mapscale+width2;
  *y = (*y-cam.y)*cam.mapscale+height2;
}

void Window::drawpixel(float x,float y, int r, int g, int b) { 
  SDL_Rect pixel;
  pixel.x = x;
  pixel.y = y;
  pixel.w = cam.mapscale/2;
  pixel.h = cam.mapscale/2;
  SDL_SetRenderDrawColor(renderer, r,g,b,255);
  SDL_RenderFillRect(renderer, &pixel);
}

void Window::drawbox(float x,float y, float w, float h, int r, int g, int b) { 
  SDL_Rect pixel;
  pixel.x = x;
  pixel.y = y;
  pixel.w = cam.mapscale*w;
  pixel.h = cam.mapscale*h;
  SDL_SetRenderDrawColor(renderer, r,g,b,255);
  SDL_RenderDrawRect(renderer, &pixel);
}


void Window::drawcircle(float centreX, float centreY, float radius, int r, int g, int b) {
  SDL_SetRenderDrawColor(renderer, r,g,b,255);
  const float diameter = (radius * 2);

  float x = (radius - 1);
  float y = 0;
  float tx = 1;
  float ty = 1;
  float error = (tx - diameter);

  while (x >= y)
  {
  // Each of the following renders an octant of the circle
  SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
  SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
  SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
  SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
  SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
  SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
  SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
  SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

    if (error <= 0)
    {
    	++y;
    	error += ty;
    	ty += 2;
    }

    if (error > 0)
    {
    	--x;
    	tx += 2;
    	error += (tx - diameter);
    }

  }
}

void Window::drawmap() {
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
  SDL_RenderClear(renderer);
  for(int i = 0; i < width; i++) {
     SDL_SetRenderDrawColor(renderer, 55, 15, 15, 0xFF);
     SDL_RenderDrawLine(renderer, (i-cam.x)*cam.mapscale+width2, 0,  (i-cam.x)*cam.mapscale+width2, height);
  } 
  for(int i = 0; i < height; i++) {
     SDL_SetRenderDrawColor(renderer, 55, 15, 15, 0xFF);
     SDL_RenderDrawLine(renderer, 0, (i-cam.y)*cam.mapscale+height2, width, (i-cam.y)*cam.mapscale+height2);
  }

  SDL_SetRenderDrawColor(renderer, 15, 15, 15, 0xFF);
  /* 
  float x = cam.x, y = cam.y;
  adjustCoords2D(&x, &y);
  x = cam.mousex; y = cam.mousey;
  adjustCoords2D(&x, &y);
  drawpixel(x, y, 255, 0, 255); //mouse position
  */
}

void Window::clear() {
  drawmap();
}

void Window::draw(World w) {
  for (int i = 0; i < w.objc; i++) {
    Object obj = w.copyobj(i);
    switch (obj.type) {
      case PARTICLE:
        drawpixel(obj.pos.x, obj.pos.y, 0, 255, 255);
        break;
      case CIRCLE:
        drawcircle(obj.pos.x, obj.pos.y, obj.radius, 255, 0, 0);
        break;
    case BOX:
        drawbox(obj.pos.x, obj.pos.y, obj.width, obj.height, 0, 255, 0);
      break;
    default:
      break;
    }
  }
}

void Window::update() {
  SDL_RenderPresent(renderer);
}

void Window::adjustMouseCoords(int *x, int *y) {
  *x = (*x-width2)/cam.mapscale + cam.x - 1;
  if (*x >= cam.x) *x = *x + 1;
  *y = (*y-height2)/cam.mapscale + cam.y - 1;
  if (*y >= cam.y) *y = *y + 1;
}

void Window::check_updates() {
  while(SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
        running = 0;
        printf("Window closed without error.\n");
        break;
    }
    int X, Y;
    SDL_GetMouseState(&X, &Y);
    adjustMouseCoords(&X, &Y);
    cam.mousex = X; cam.mousey = Y;
  }
}

void Window::kill() {
  running = 0;
  SDL_DestroyWindow(win);
  SDL_Quit();
}

Window::Window(char *title, int w, int h) {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    printf("SDL failed to initialize!\n%s\n", SDL_GetError());
    running = 0;
    return;
  }
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

  win = SDL_CreateWindow(title, 256, 64, w, h, SDL_WINDOW_OPENGL);
  renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
  SDL_GL_CreateContext(win);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    printf("Failed to load OPENGL!\n%s\n", SDL_GetError());
    running = 0;
    return;
  }
  width = w;
  height = h;
  width2 = w/2;
  height2 = h/2;

  running = 1;
  SDL_ShowCursor(1);

  cam.x = 50;
  cam.y = 50;
  cam.mapscale = 8;
}

Window::Window() {}

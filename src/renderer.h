#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include "SDL.h"
#include "snake.h"
#include "TextureLoader.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();
  void Render(SDL_Texture*);
  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);
  SDL_Renderer* getrenderer();
  
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

 /*Informational screen texture pointers*/
  SDL_Texture *title_screen;
  SDL_Texture *game_over_screen;
 
 /*Initial run indicator used to render titlescreen*/
  bool initialRun;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif

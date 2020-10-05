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
  void Render(Gamestate&);
  void Render(Snake const snake, SDL_Point const &food);
  void UpdateWindowTitle(int score, int fps);
  SDL_Renderer* getrenderer();
  
 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
  
  // Path to images for info screens
  const char* title_screen_png = "../images/Title.png";
  const char* game_over_png = "../images/GameOver.png";
  const char* pause_screen_png = "../images/Paused.png";
};

#endif

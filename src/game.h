#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game;
class Controller;
class Renderer;

class Gamestate {
public:
  bool running = false;
  bool title = false;
  bool gameover = false;
  bool paused = false;
  bool reset = false;
  void Check(Game &game, Renderer &renderer, Snake &snake, Controller const &controller);
};


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  Gamestate gamestate;
  void Reset();
 private:
  Snake snake;
  SDL_Point food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void PlaceFood();
  void Update();
  
};

#endif

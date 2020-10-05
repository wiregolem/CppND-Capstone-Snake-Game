#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "snake.h"
#include "game.h"
class Gamestate;

class Controller {
 public:
  void HandleInput(Gamestate &gamestate, Snake &snake) const;

 private:
  void ChangeDirection(Gamestate &gamestate,Snake &snake, Snake::Direction input,
                       Snake::Direction opposite) const;
};

#endif

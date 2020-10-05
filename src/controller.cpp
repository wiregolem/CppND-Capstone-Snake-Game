#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "snake.h"

void Controller::ChangeDirection(Gamestate &gamestate,Snake &snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if ((snake.direction != opposite || snake.size == 1)&& !gamestate.paused) snake.direction = input;
  return;
}

void Controller::HandleInput(Gamestate &gamestate,  Snake &snake) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      //End game
      gamestate.running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(gamestate,snake, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;

        case SDLK_DOWN:
          ChangeDirection(gamestate,snake, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(gamestate,snake, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(gamestate,snake, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
       case SDLK_ESCAPE:
         //End game
	 gamestate.running = false;
         gamestate.title = false;
         gamestate.gameover = false;
         gamestate.paused = false;
         gamestate.reset = false;
	  break;
       case SDLK_SPACE:
	  // If not on an info screen, pause the game, else resume
          if(!gamestate.title && !gamestate.gameover && !gamestate.paused){
            gamestate.paused=true;
          }
            else if(gamestate.paused){
              gamestate.paused=false;
            }
          //Reset Game from game over screen
          if(gamestate.gameover) {
            gamestate.gameover = false;
            gamestate.reset = true;
          }
          //Leave title screen and begin gameplay
          if(gamestate.title){
            gamestate.title = false;
          }
          break;
      }
    }
  }
}


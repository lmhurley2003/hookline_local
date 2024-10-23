/**
 * @file Application.hpp
 *
 * Handles making the window and running the event/game loop.
 */

#pragma once
#include <SDL2/SDL.h>

#include "Game.hpp"

class Application {
   public:
    bool init();
    void run();

   private:
    SDL_Window* window_;
    SDL_GLContext context_;
    Game game_;
    bool quit_ = false;
};
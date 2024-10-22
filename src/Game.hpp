#pragma once
#include <SDL2/SDL.h>

class Game {
   public:
    bool init();
    void run();

   private:
    SDL_Window *window_;
    SDL_GLContext context_;
};
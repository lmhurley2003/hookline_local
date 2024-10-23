/**
 * @file Game.hpp
 *
 * Handles game state, update, rendering, etc.
 */

#pragma once

#include <SDL2/SDL_events.h>

#include <glm/glm.hpp>

#include "shader/PlayerTestShaderProgram.hpp"

class Game {
   public:
    void update(float dt);
    void render(glm::uvec2 const &drawable_size);
    bool handle_event(SDL_Event const &event);

   private:
    struct Player {
        glm::vec2 position = {0.0f, 0.0f};
        glm::vec2 velocity = {0.0f, 0.0f};
        glm::vec2 size = {0.1f, 0.1f};

        struct Button {
            bool pressed;
        };
        Button up, down, left, right;

        // Rendering -- obviously bad, just for demo
        PlayerTestShaderProgram program;
        std::array<float, 8> vertices();
        void render();
    } player_;
};
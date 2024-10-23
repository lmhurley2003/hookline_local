/**
 * @file Game.hpp
 *
 * Handles game state, update, rendering, etc.
 */

#pragma once

#include <glm/glm.hpp>

class Game {
   public:
    void update(float dt);
    void render(glm::uvec2 const &drawable_size);

   private:
    struct Player {
        glm::vec2 position;
        glm::vec2 velocity;
    } player_;
};
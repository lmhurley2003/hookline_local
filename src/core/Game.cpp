/**
 * @file Game.cpp
 *
 * Implement Game.hpp
 */

#include "Game.hpp"

#include <GL/glew.h>

void Game::update(float dt) {
    (void)dt;
    player_.position += player_.velocity * dt;
}

void Game::render(glm::uvec2 const &drawable_size) {
    (void)drawable_size;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
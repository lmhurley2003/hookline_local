/**
 * @file Game.cpp
 *
 * Implement Game.hpp
 */

#include "Game.hpp"

#include <GL/glew.h>

#include <glm/common.hpp>

#include "physics/Components.hpp"

void Game::update(float dt) {
    (void)dt;
    // constexpr float velocity = 0.75f;
    // Input
    player_.forces = ForceComponent();
    if (player_.up.pressed) {
        player_.forces.add_force({0, 2.0f});
    }
    if (player_.down.pressed) {
        player_.forces.add_force({0, -2.0f});
    }
    if (player_.left.pressed) {
        player_.forces.add_force({-1.0f, 0.0f});
    }
    if (player_.right.pressed) {
        player_.forces.add_force({1.0f, 0.0f});
    }
    player_.transform.position += player_.rigid_body.velocity * dt;

    // Physics
    auto x = std::vector({std::make_tuple(&player_.rigid_body, &player_.forces,
                                          &player_.transform)});
    physics->update(dt, x);
}

void Game::render(glm::uvec2 const &drawable_size) {
    (void)drawable_size;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    player_.renderable.render(player_.transform);
}

bool Game::handle_event(SDL_Event const &event) {
    if (event.type == SDL_KEYDOWN) {
        if (event.key.keysym.sym == SDLK_a) {
            player_.left.pressed = true;
            return true;
        } else if (event.key.keysym.sym == SDLK_d) {
            player_.right.pressed = true;
            return true;
        } else if (event.key.keysym.sym == SDLK_w) {
            player_.up.pressed = true;
            return true;
        } else if (event.key.keysym.sym == SDLK_s) {
            player_.down.pressed = true;
            return true;
        }
    } else if (event.type == SDL_KEYUP) {
        if (event.key.keysym.sym == SDLK_a) {
            player_.left.pressed = false;
            return true;
        } else if (event.key.keysym.sym == SDLK_d) {
            player_.right.pressed = false;
            return true;
        } else if (event.key.keysym.sym == SDLK_w) {
            player_.up.pressed = false;
            return true;
        } else if (event.key.keysym.sym == SDLK_s) {
            player_.down.pressed = false;
            return true;
        }
    }
    return false;
}
/**
 * @file Game.cpp
 *
 * Implement Game.hpp
 */

#include "Game.hpp"

#include <GL/glew.h>

#include <glm/common.hpp>
#include <memory>

#include "core/RenderComponent.hpp"
#include "core/TransformComponent.hpp"
#include "physics/Components.hpp"
#include "physics/PhysicsSystem.hpp"

namespace {
static std::vector<glm::vec2> get_basic_shape() {
    return {/*BL*/ {-0.5, -0.5}, /*BR*/ {0.5, -0.5},
            /*TL*/ {-0.5, 0.5}, /*TR*/ {0.5, 0.5}};
}
}  // namespace

Game::Game()
    : physics(std::make_unique<PhysicsSystem>()),
      registry(std::make_unique<entt::registry>()) {
    // Initialize player
    auto entity = registry->create();
    registry->emplace<TransformComponent>(entity, glm::vec2{0.0f, 0.0f},
                                          glm::vec2{0.05f, 0.05f});
    registry->emplace<RigidBodyComponent>(entity);
    registry->emplace<ForceComponent>(entity);
    registry->emplace<RenderComponent>(entity, get_basic_shape());
    registry->emplace<PlayerComponent>(entity);
    player_.entity = entity;
}

void Game::update(float dt) {
    (void)dt;
    // Input
    auto &forces = registry->get<ForceComponent>(player_.entity);
    auto &transform = registry->get<TransformComponent>(player_.entity);
    auto &rigid_body = registry->get<RigidBodyComponent>(player_.entity);

    forces.set_force({0.0, 0.0f});
    if (player_.up.pressed) {
        forces.set_force({0, 2.0f});
    }
    if (player_.down.pressed) {
        forces.set_force({0, -2.0f});
    }
    if (player_.left.pressed) {
        forces.set_force({-1.0f, 0.0f});
    }
    if (player_.right.pressed) {
        forces.set_force({1.0f, 0.0f});
    }
    transform.position += rigid_body.velocity * dt;

    // Physics
    physics->update(dt, *registry.get());
}

void Game::render(glm::uvec2 const &drawable_size) {
    (void)drawable_size;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto view = registry->view<TransformComponent, RenderComponent>();
    for (auto entity : view) {
        auto &transform = view.get<TransformComponent>(entity);
        auto &renderable = view.get<RenderComponent>(entity);
        renderable.render(transform);
    }
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
/**
 * @file Game.hpp
 *
 * Handles game state, update, rendering, etc.
 */

#pragma once

#include <SDL2/SDL_events.h>

#include <entt/entity/fwd.hpp>
#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <memory>
#include <physics/Components.hpp>

#include "physics/PhysicsSystem.hpp"

class Game {
   public:
    Game();

    void update(float dt);
    void render(glm::uvec2 const &drawable_size);
    bool handle_event(SDL_Event const &event);

    struct PlayerComponent {
    } player;
    struct Player {
        entt::entity entity;
        struct Button {
            bool pressed;
        };
        Button up, down, left, right;
    } player_;

    std::unique_ptr<PhysicsSystem> physics;
    std::unique_ptr<entt::registry> registry;
};
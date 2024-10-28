/**
 * @file Game.hpp
 *
 * Handles game state, update, rendering, etc.
 */

#pragma once

#include <SDL2/SDL_events.h>

#include <glm/glm.hpp>
#include <memory>
#include <physics/Components.hpp>

#include "TransformComponent.hpp"
#include "core/RenderComponent.hpp"
#include "physics/PhysicsSystem.hpp"

class Game {
   public:
    Game() = default;

    void update(float dt);
    void render(glm::uvec2 const &drawable_size);
    bool handle_event(SDL_Event const &event);

    struct Player {
        TransformComponent transform;
        RigidBodyComponent rigid_body;
        ForceComponent forces;
        RenderComponent renderable;

        struct Button {
            bool pressed;
        };
        Button up, down, left, right;

        static std::vector<glm::vec2> get_vertices() {
            return {/*BL*/ {-0.5, -0.5}, /*BR*/ {0.5, -0.5},
                    /*TL*/ {-0.5, 0.5}, /*TR*/ {0.5, 0.5}};
        }

        Player() : renderable(get_vertices()) {};
        ~Player() = default;
    } player_;

    std::unique_ptr<PhysicsSystem> physics;
};
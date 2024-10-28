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
#include "physics/PhysicsSystem.hpp"
#include "shader/PlayerTestShaderProgram.hpp"

class Game {
   public:
    void update(float dt);
    void render(glm::uvec2 const &drawable_size);
    bool handle_event(SDL_Event const &event);

    struct Player {
        TransformComponent transform;
        RigidBodyComponent rigid_body;
        ForceComponent forces;

        struct Button {
            bool pressed;
        };
        Button up, down, left, right;

        // Rendering -- obviously bad, just for demo
        PlayerTestShaderProgram program;
        std::array<float, 8> vertices();
        void render();
    } player_;

    std::unique_ptr<PhysicsSystem> physics;
};
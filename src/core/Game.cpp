/**
 * @file Game.cpp
 *
 * Implement Game.hpp
 */

#include "Game.hpp"

#include <GL/glew.h>
#include <SDL2/SDL.h>

#include <glm/glm.hpp>

#include "core/InputComponent.hpp"
#include "core/RenderComponent.hpp"
#include "core/TransformComponent.hpp"
#include "physics/Components.hpp"
#include "physics/GrapplingHook.hpp"
#include "physics/PhysicsSystem.hpp"
#include "physics/util.hpp"

namespace {
static std::vector<glm::vec2> get_basic_shape() {
    return {/*BL*/ {-0.5, -0.5}, /*BR*/ {0.5, -0.5},
            /*TL*/ {-0.5, 0.5}, /*TR*/ {0.5, 0.5}};
}
}  // namespace

Game::Game() {
    // Initialize player
    {
        auto player = registry.create();
        registry.emplace<TransformComponent>(
            player, TransformComponent(glm::vec2{0.0f, 0.0f},
                                       glm::vec2{0.05f, 0.05f}, 0.0f));
        registry.emplace<RigidBodyComponent>(player);
        registry.emplace<ForceComponent>(player);
        registry.emplace<ColliderComponent>(player, glm::vec2{1.0f, 1.0f});
        registry.emplace<RenderComponent>(player, get_basic_shape());
        registry.emplace<InputComponent>(player);
        player_.entity = player;
    }

    // Create an immovable box somewhere
    {
        auto box = registry.create();
        registry.emplace<TransformComponent>(
            box, TransformComponent(glm::vec2{0.5f, 0.5f},
                                    glm::vec2{0.05f, 0.05f}, 0.0f));
        registry.emplace<RigidBodyComponent>(box);
        registry.emplace<ColliderComponent>(box, glm::vec2{1.0f, 1.0f}, false);
        registry.emplace<RenderComponent>(box, get_basic_shape());
    }

    // Create grappling hook
    {
        grapple_entity = registry.create();
        registry.emplace<TransformComponent>(
            grapple_entity, TransformComponent(glm::vec2(0.0f, 0.0f),
                                               glm::vec2{0.05f, 0.05f}, 0.0f));
        registry.emplace<GrapplingHookComponent>(grapple_entity, grapple_entity,
                                                 player_.entity);
        registry.emplace<RenderComponent>(grapple_entity, get_basic_shape());
    }
}

void Game::update(float dt) {
    (void)dt;
    // Input

    /* -- PLAYER INPUT & GRAPPLE -- */
    // TODO: Put input into a separate input component and handle this movement
    auto &inputs = registry.get<InputComponent>(player_.entity);
    constexpr float force_amount = 30.0f;
    inputs.movement = {0.0f, 0.0f};
    if (player_.up.pressed) {
        inputs.movement += glm::vec2{0.0f, force_amount};
    }
    if (player_.down.pressed) {
        inputs.movement += glm::vec2{0, -force_amount};
    }
    if (player_.left.pressed) {
        inputs.movement += glm::vec2{-force_amount, 0.0f};
    }
    if (player_.right.pressed) {
        inputs.movement += glm::vec2{force_amount, 0.0f};
    }
    // Grapple inputs - all manual stuff, fix later
    auto &player_transform = registry.get<TransformComponent>(player_.entity);
    auto [grapple_transform, grapple_renderable, grapple] =
        registry
            .get<TransformComponent, RenderComponent, GrapplingHookComponent>(
                grapple_entity);
    grapple_transform.position = player_transform.position;
    if (player_.mouse.pressed) {
        grapple.try_attach(player_transform.position, player_.mouse.position,
                           registry);
    }
    if (!player_.mouse.pressed) {
        grapple.detach();
    }
    // Grapple rendering setup
    grapple_renderable.set_visible(grapple.attached);
    if (grapple.attached) {
        grapple_transform.position =
            (player_transform.position + grapple.attached_position) / 2.0f;
        grapple_transform.scale = {
            glm::distance(player_transform.position, grapple.attached_position),
            0.01};
        glm::vec2 direction = glm::normalize(grapple.attached_position -
                                             player_transform.position);
        grapple_transform.rotation = -glm::atan(direction.y, direction.x);
    }

    // Physics
    physics.update(dt, registry);

    // Collision
    collisions.update(dt, registry);
}

void Game::render(glm::uvec2 drawable_size) {
    (void)drawable_size;
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    auto view = registry.view<TransformComponent, RenderComponent>();
    for (auto entity : view) {
        auto &transform = view.get<TransformComponent>(entity);
        auto &renderable = view.get<RenderComponent>(entity);
        renderable.render(transform);
    }
}

bool Game::handle_event(SDL_Event const &event, glm::uvec2 drawable_size) {
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
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            int x, y;
            SDL_GetMouseState(&x, &y);
            player_.mouse.pressed = true;
            player_.mouse.position =
                hookline::convert_mouse_to_opengl(x, y, drawable_size);
        }
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            player_.mouse.pressed = false;
        }
    }
    return false;
}
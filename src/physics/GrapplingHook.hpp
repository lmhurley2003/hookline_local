#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "physics/util.hpp"

struct GrapplingHookComponent {
    static constexpr float max_length = 10.0f;
    static constexpr float pull_force = 30.0f;
    static constexpr float deactivate_dist = 0.01f;

    entt::entity user;
    bool attached = false;
    glm::vec2 attached_position;
    float curr_length = 0.0f;

    void try_attach(glm::vec2 start_position, glm::vec2 target_position,
                    entt::registry &registry) {
        if (attached) {
            return;
        }

        glm::vec2 hit_position;
        glm::vec2 direction = glm::normalize(target_position - start_position);
        if (hookline::raycast(start_position, direction, max_length, registry,
                              &hit_position)) {
            std::cout << "Attached grapple\n";
            attached = true;
            attached_position = hit_position;
        }
    }

    void detach() {
        if (!attached) {
            return;
        }
        attached = false;
        std::cout << "Detached grapple\n";
    }

    GrapplingHookComponent(entt::entity user_) : user(user_) {}
};
#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <iostream>

#include "constants.hpp"
#include "physics/util.hpp"

struct GrapplingHookComponent {
    static constexpr float max_length = hookline::grapple_max_length;
    static constexpr float pull_force = hookline::grapple_pull_force;
    static constexpr float deactivate_dist = hookline::grapple_deactive_dist;

    entt::entity self;
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
        std::vector<entt::entity> ignore_list = {user, self};
        if (hookline::raycast(start_position, direction, max_length, registry,
                              ignore_list, &hit_position)) {
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

    GrapplingHookComponent(entt::entity self_, entt::entity user_)
        : self(self_), user(user_) {}
};
#pragma once

#include <glm/glm.hpp>
#include <numeric>
#include <vector>

#include "constants.hpp"

struct RigidBodyComponent {
    float mass = 1.0f;
    // float drag;
    glm::vec2 velocity = {0.0f, 0.0f};

    void clamp_velocity() {
        velocity = glm::clamp(velocity, -hookline::max_velocity,
                              hookline::max_velocity);
    }
};

struct ForceComponent {
    std::vector<glm::vec2> linear_forces;

    // TODO: preallocate memory for common forces
    // TODO: rotational forces?

    void set_force(glm::vec2 linear_force) {
        linear_forces.clear();
        add_force(linear_force);
    }

    void add_force(glm::vec2 linear_force) {
        linear_forces.push_back(linear_force);
    }

    glm::vec2 net_force() {
        return std::accumulate(linear_forces.begin(), linear_forces.end(),
                               glm::vec2{0.0f, 0.0f});
    }
};

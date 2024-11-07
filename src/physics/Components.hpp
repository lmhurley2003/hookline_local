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
        reset();
        add_force(linear_force);
    }

    void add_force(glm::vec2 linear_force) {
        linear_forces.push_back(linear_force);
    }

    glm::vec2 net_force() {
        return std::accumulate(linear_forces.begin(), linear_forces.end(),
                               glm::vec2{0.0f, 0.0f});
    }

    void reset() { linear_forces.clear(); }
};

/**
 * Component in any objects than can collide (2D Axis Aligned Bounding Box)
 *
 * Width/height should be half of the object's relative width/height. We assume
 * the position is at the center of the object
 */
struct ColliderComponent {
    glm::vec2 size;
    bool can_collide = true;
    bool can_move = true;

    ColliderComponent(glm::vec2 size_) : size(size_) {};
    ColliderComponent(glm::vec2 size_, bool can_collide_, bool can_move_)
        : size(size_), can_collide(can_collide_), can_move(can_move_) {};
};

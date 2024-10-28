#include "PhysicsSystem.hpp"

#include <iostream>

#include "constants.hpp"
#include "core/TransformComponent.hpp"

constexpr glm::vec2 g_accel() { return {0.0f, hookline::g}; }

void PhysicsSystem::update(
    float dt,
    std::vector<std::tuple<RigidBodyComponent *, ForceComponent *,
                           TransformComponent *>> &physics_components) {
    for (auto &[rigid_body, forces, transform] : physics_components) {
        glm::vec2 force = forces->net_force();
        rigid_body->velocity += (force / rigid_body->mass + g_accel()) * dt;
        rigid_body->velocity *= 1.0f - (hookline::drag * dt);
        rigid_body->clamp_velocity();
        transform->position += rigid_body->velocity * dt;
    }
}
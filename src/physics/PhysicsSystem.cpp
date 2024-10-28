#include "PhysicsSystem.hpp"

#include "constants.hpp"
#include "core/TransformComponent.hpp"
#include "physics/Components.hpp"

constexpr glm::vec2 g_accel() { return {0.0f, hookline::g}; }
void PhysicsSystem::update(float dt, entt::registry& registry) {
    auto view =
        registry.view<RigidBodyComponent, ForceComponent, TransformComponent>();
    for (auto [entity, rigid_body, forces, transform] : view.each()) {
        glm::vec2 force = forces.net_force();
        rigid_body.velocity += (force / rigid_body.mass + g_accel()) * dt;
        rigid_body.velocity -= hookline::drag * rigid_body.velocity * dt;
        rigid_body.clamp_velocity();
        transform.position += rigid_body.velocity * dt;
    }
}
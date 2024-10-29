#include "CollectableSystem.hpp"

#include <entt/entt.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>
#include <iostream>

#include "CollectableComponent.hpp"
#include "core/RenderComponent.hpp"
#include "core/TransformComponent.hpp"
#include "util/misc.hpp"

void CollectableSystem::update(float dt, entt::registry &registry,
                               entt::entity player) {
    (void)dt;
    auto player_position = registry.get<TransformComponent>(player).position;
    auto view = registry.view<TransformComponent, CollectableComponent>();
    for (auto [entity, transform, collectable] : view.each()) {
        if (glm::distance(transform.position, player_position) <= 0.1f) {
            on_pickup(registry, entity);
        }
    }
}

void CollectableSystem::spawn(entt::registry &registry, glm::vec2 position) {
    auto collectable = registry.create();
    registry.emplace<TransformComponent>(
        collectable,
        TransformComponent(position, glm::vec2{0.025f, 0.025f}, 0.0f));
    registry.emplace<CollectableComponent>(collectable);
    registry.emplace<RenderComponent>(collectable,
                                      hookline::get_basic_shape_debug());

    std::cout << "Spawning collectable " << static_cast<uint32_t>(collectable)
              << " with position " << "(" << position.x << ", " << position.y
              << ")\n";
}

void CollectableSystem::spawn_random(entt::registry &registry) {
    glm::vec2 random_position =
        glm::linearRand(glm::vec2{-1.0f, -1.0f}, glm::vec2{1.0f, 1.0f});
    spawn(registry, random_position);
}

void CollectableSystem::on_pickup(entt::registry &registry,
                                  entt::entity collectable) {
    std::cout << "Picked up " << static_cast<uint32_t>(collectable) << "\n";
    registry.destroy(collectable);
    spawn_random(registry);
}
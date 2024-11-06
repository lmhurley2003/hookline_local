#include "CameraSystem.hpp"

#include <entt/entt.hpp>

#include "core/CameraComponent.hpp"
#include "core/TransformComponent.hpp"

CameraSystem::CameraSystem(entt::entity &player_entity)
    : player_entity_(player_entity) {}

void CameraSystem::update(float dt, entt::registry &registry) {
    (void)dt;

    auto &player_transform = registry.get<TransformComponent>(player_entity_);
    /* Make camera(s) follow player */
    for (auto [_, camera_transform, camera] :
         registry.view<TransformComponent, CameraComponent>().each()) {
        camera_transform.position = player_transform.position;
    }
}
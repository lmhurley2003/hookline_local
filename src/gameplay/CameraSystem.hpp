#pragma once

#include <entt/entt.hpp>

class CameraSystem {
   public:
    explicit CameraSystem(entt::entity &player_entity);

    void update(float dt, entt::registry &registry);

   private:
    entt::entity &player_entity_;
};
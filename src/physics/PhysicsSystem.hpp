#pragma once

#include <entt/entt.hpp>

class PhysicsSystem {
   public:
    void update(float dt, entt::registry &registry);
};
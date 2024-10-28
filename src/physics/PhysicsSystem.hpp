#pragma once

#include "core/TransformComponent.hpp"
#include "physics/Components.hpp"

class PhysicsSystem {
   public:
    void update(
        float dt,
        std::vector<std::tuple<RigidBodyComponent *, ForceComponent *,
                               TransformComponent *>> &physics_components);
};
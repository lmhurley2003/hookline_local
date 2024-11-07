#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

class RenderSystem {
   public:
    void render(glm::uvec2 drawable_size, entt::registry &registry,
                entt::entity camera);
};
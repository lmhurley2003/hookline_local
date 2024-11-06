#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

class RenderSystem {
   public:
    void render(glm::uvec2 drawable_size, const entt::registry &registry);
};
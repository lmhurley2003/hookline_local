#include "util.hpp"

#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include "core/TransformComponent.hpp"
#include "physics/Components.hpp"

namespace hookline {
bool point_in_rect(glm::vec2 point, glm::vec2 rect_position,
                   glm::vec2 rect_size) {
    return (point.x >= rect_position.x - rect_size.x / 2 &&
            point.x <= rect_position.x + rect_size.x / 2 &&
            point.y >= rect_position.y - rect_size.y / 2 &&
            point.y <= rect_position.y + rect_size.y / 2);
}

bool raycast(glm::vec2 start, glm::vec2 direction, float max_length,
             entt::registry& registry, glm::vec2* hit_position) {
    direction = glm::normalize(direction);

    auto view = registry.view<TransformComponent, ColliderComponent>();
    float curr_length = 0.0f;
    bool did_hit = false;
    // Iterative ray extension
    while (curr_length <= max_length) {
        for (const auto [_, transform, collider] : view.each()) {
            // Check for ray intersection
            glm::vec2 curr_position = start + direction * curr_length;
            if (point_in_rect(curr_position, transform.position,
                              collider.size)) {
                // Ray intersected
                *hit_position = curr_position;
                did_hit = true;
            }
        }
        curr_length += 0.1f;
    }

    return did_hit;
}

/**
 * Convert a mouse position from SDL_GetMouseState to OpenGL coordinates
 * TODO: Should probably move this
 */
glm::vec2 convert_mouse_to_opengl(int x, int y, glm::uvec2 drawable_size) {
    glm::vec2 result;
    result.x = (2.0f * x) / drawable_size.x - 1.0f;
    result.y = 1.0f - (2.0f * y) / drawable_size.y;
    return result;
}

}  // namespace hookline
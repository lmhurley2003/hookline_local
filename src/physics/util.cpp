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

bool line_intersects_rect(glm::vec2 start, glm::vec2 end,
                          glm::vec2 rect_position, glm::vec2 rect_size,
                          glm::vec2* hit_position) {
    float left = rect_position.x - rect_size.x / 2;
    float right = rect_position.x + rect_size.x / 2;
    float top = rect_position.y + rect_size.y / 2;
    float bottom = rect_position.y - rect_size.y / 2;

    // Short Circuit - Line is completely to one side of rectangle
    if (start.x <= left && end.x <= left) return false;
    if (start.x >= right && end.x >= right) return false;
    if (start.y >= top && end.y >= top) return false;
    if (start.y <= bottom && end.y <= bottom) return false;

    // Check intersections at any edges
    float m = (end.y - start.y) / (end.x - start.x);

    // Bottom edge - technically the most likely
    float x_at_bottom_edge = (bottom - start.y) / m + start.x;
    if (x_at_bottom_edge > left && x_at_bottom_edge < right) {
        *hit_position = glm::vec2{x_at_bottom_edge, bottom};
        return true;
    }

    // Left edge
    float y_at_left_edge = m * (left - start.x) + start.y;
    if (y_at_left_edge < top && y_at_left_edge > bottom) {
        *hit_position = glm::vec2{left, y_at_left_edge};
        return true;
    };

    // Right edge
    float y_at_right_edge = m * (right - start.x) + start.y;
    if (y_at_right_edge < top && y_at_right_edge > bottom) {
        *hit_position = glm::vec2{right, y_at_right_edge};
        return true;
    }

    // Top edge
    float x_at_top_edge = (top - start.y) / m + start.x;
    if (x_at_top_edge > left && x_at_top_edge < right) {
        *hit_position = glm::vec2{x_at_top_edge, top};
        return true;
    }

    return false;
}

bool raycast(glm::vec2 start, glm::vec2 direction, float max_length,
             entt::registry& registry,
             const std::vector<entt::entity>& ignore_list,
             glm::vec2* hit_position) {
    direction = glm::normalize(direction);

    auto view = registry.view<TransformComponent, ColliderComponent>();
    bool did_hit = false;
    // Iterative ray extension
    for (const auto [entity, transform, collider] : view.each()) {
        // Check for ray intersection, ignore starting in a collider
        if (line_intersects_rect(
                start, start + direction * max_length, transform.position,
                collider.size * transform.scale, hit_position) &&
            std::find(ignore_list.begin(), ignore_list.end(), entity) ==
                ignore_list.end()) {
            did_hit = true;
            break;
        }
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
#pragma once

#include <entt/entt.hpp>
#include <glm/glm.hpp>

namespace hookline {
/**
 * Assume the position is the center of the square and the size is the full
 * width/height
 */
bool point_in_rect(glm::vec2 point, glm::vec2 rect_position,
                   glm::vec2 rect_size);

/**
 * Line-Rectangle detection (adapted)
 * Main Source:
 * https://www.jeffreythompson.org/collision-detection/line-rect.php
 */
bool line_intersects_rect(glm::vec2 start, glm::vec2 end,
                          glm::vec2 rect_position, glm::vec2 rect_size,
                          glm::vec2* hit_position);

/**
 * Check for a ray hit on any colliders
 */
bool raycast(glm::vec2 start, glm::vec2 direction, float max_length,
             entt::registry& registry,
             const std::vector<entt::entity>& ignore_list,
             glm::vec2* hit_position);

glm::vec2 convert_mouse_to_opengl(int x, int y, glm::uvec2 drawable_size);

}  // namespace hookline
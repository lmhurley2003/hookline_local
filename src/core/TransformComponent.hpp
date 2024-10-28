#pragma once

#include <glm/glm.hpp>

struct TransformComponent {
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 scale = {0.25f, 0.25f};
};

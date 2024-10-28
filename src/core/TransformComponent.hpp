#pragma once

#include <glm/glm.hpp>

struct TransformComponent {
    glm::vec2 position = {0.0f, 0.0f};
    glm::vec2 scale = {0.25f, 0.25f};

    TransformComponent() = default;
    TransformComponent(glm::vec2 position_, glm::vec2 scale_)
        : position(position_), scale(scale_) {}
};

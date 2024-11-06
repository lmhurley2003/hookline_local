#pragma once

#include <glm/glm.hpp>

/**
 * Component on a camera.
 *
 * viewport_size should be updated before rendering every frame (assuming
 * allowed window resize)
 */
struct CameraComponent {
    glm::vec2 viewport_size;
    float pixels_per_unit;

    explicit CameraComponent(glm::vec2 viewport_size, float pixels_per_unit)
        : viewport_size(viewport_size), pixels_per_unit(pixels_per_unit) {}
};
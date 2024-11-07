#pragma once

#include <glm/glm.hpp>

struct Vertex {
    glm::vec2 position;
    glm::vec2 tex_coords;
    glm::vec4 color;

    Vertex() = default;
    Vertex(glm::vec2 position, glm::vec2 tex_coords, glm::vec4 color)
        : position(position), tex_coords(tex_coords), color(color) {}
};

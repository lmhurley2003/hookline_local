#include "RenderComponent.hpp"

RenderComponent::RenderComponent(std::vector<glm::vec2>&& vertices,
                                 bool visible)
    : vao_(0), vbo_(0), verts_(std::move(vertices)), visible_(visible) {
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
}

RenderComponent::~RenderComponent() {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

void RenderComponent::set_visible(bool visible) { visible_ = visible; }
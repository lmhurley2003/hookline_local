#include "RenderComponent.hpp"

/**
 * Make a new RenderComponent using vertices and a (default) color.
 */
RenderComponent RenderComponent::from_vertices_color(
    const std::vector<glm::vec2>& vertices, glm::vec4 color) {
    RenderComponent result;
    for (glm::vec2 vertex_pos : vertices) {
        Vertex vertex = {vertex_pos, glm::vec2{0.0f, 0.0f}, color};
        result.verts_.push_back(vertex);
    }
    result.visible_ = true;
    result.use_texture_ = false;

    result.setup();

    return result;
}

/**
 * Make a new RenderComponent using vertices and a texture;
 */
RenderComponent RenderComponent::from_vertices_texture(
    const std::vector<glm::vec2>& vertices,
    const std::vector<glm::vec2>& tex_coords, GLuint texture) {
    assert(vertices.size() == tex_coords.size() &&
           "RenderComponent: Cannot construct with different length vertices "
           "and tex_coords");
    assert(texture != 0 && "RenderComponent: Need a valid texture");

    RenderComponent result;
    for (size_t i = 0; i < vertices.size(); ++i) {
        Vertex vertex = {vertices[i], tex_coords[i], {0.0f, 0.0f, 0.0f, 1.0f}};
        result.verts_.push_back(vertex);
    }
    result.texture_ = texture;
    result.visible_ = true;
    result.use_texture_ = true;

    result.setup();

    return result;
}

RenderComponent::~RenderComponent() { cleanup(); }

RenderComponent::RenderComponent(RenderComponent&& other) noexcept
    : program_(std::move(other.program_)),
      vao_(other.vao_),
      vbo_(other.vbo_),
      verts_(std::move(other.verts_)),
      texture_(other.texture_),
      visible_(other.visible_),
      use_texture_(other.use_texture_) {
    other.vao_ = 0;
    other.vbo_ = 0;
}

RenderComponent& RenderComponent::operator=(RenderComponent&& other) noexcept {
    if (this == &other) {
        return *this;
    }

    // Clean up current objects
    cleanup();

    // Move
    program_ = std::move(other.program_);
    vao_ = other.vao_;
    vbo_ = other.vbo_;
    verts_ = std::move(other.verts_);
    texture_ = other.texture_;
    visible_ = other.visible_;
    use_texture_ = other.use_texture_;

    // Reset other
    other.vao_ = 0;
    other.vbo_ = 0;

    return *this;
}

void RenderComponent::set_visible(bool visible) { visible_ = visible; }

void RenderComponent::setup() {
    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);
}

void RenderComponent::cleanup() {
    glDeleteVertexArrays(1, &vao_);
    glDeleteBuffers(1, &vbo_);
}

#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>

#include "render/Vertex.hpp"
#include "shader/PlayerTestShaderProgram.hpp"

/**
 * RenderComponent holding rendering data like a shader progrma, vertices, etc.
 *
 * Don't construct directly, call the `static RenderComponent from_***(...)`
 * methods to get an instance.
 */
class RenderComponent {
   public:
    /**
     * Make a new RenderComponent using vertices and a (default) color.
     */
    static RenderComponent from_vertices_color(
        const std::vector<glm::vec2>& vertices,
        glm::vec4 color = {0.0f, 0.0f, 0.0f, 1.0f});
    /**
     * Make a new RenderComponent using vertices and a texture;
     */
    static RenderComponent from_vertices_texture(
        const std::vector<glm::vec2>& vertices,
        const std::vector<glm::vec2>& tex_coords, GLuint texture);

    ~RenderComponent();

    // Cannot copy a render component
    RenderComponent(const RenderComponent& other) = delete;
    RenderComponent& operator=(const RenderComponent& other) = delete;

    RenderComponent(RenderComponent&& other) noexcept;
    RenderComponent& operator=(RenderComponent&& other) noexcept;

    void set_visible(bool visible);

    PlayerTestShaderProgram program_;
    GLuint vao_ = 0;  // owning
    GLuint vbo_ = 0;  // owning
    std::vector<Vertex> verts_;
    GLuint texture_ = 0;  // non-owning
    bool visible_ = true;
    bool use_texture_ = false;

   private:
    RenderComponent() = default;
    void setup();
    void cleanup();
};
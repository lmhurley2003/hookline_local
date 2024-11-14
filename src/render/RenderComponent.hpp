#pragma once

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <vector>

#include "render/Vertex.hpp"
#include "shader/BasicMeshShader.hpp"
#include "shader/GrappleBoxShader.hpp"

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
        /**
     * Make a new grapple's RenderComponent using vertices and a (default) color.
     */
    static RenderComponent grapple_from_vertices_color(
        const std::vector<glm::vec2>& vertices,
        const std::vector<glm::vec2>& tex_coords,
        glm::vec4 color = {0.0f, 0.0f, 0.0f, 1.0f});

    ~RenderComponent();

    // Cannot copy a render component
    RenderComponent(const RenderComponent& other) = delete;
    RenderComponent& operator=(const RenderComponent& other) = delete;

    RenderComponent(RenderComponent&& other) noexcept;
    RenderComponent& operator=(RenderComponent&& other) noexcept;

    void set_visible(bool visible);

    union {
       BasicMeshShader program_ = BasicMeshShader();
       GrappleBoxShader grappleProgram_;
    };

    enum objectType {
        GRAPPLE_BOX,
        PLAYER,
        OTHER
    } object_type;

    GLuint vao_ = 0;  // owning
    GLuint vbo_ = 0;  // owning
    std::vector<Vertex> verts_;
    GLuint texture_ = 0;  // non-owning
    bool visible_ = true;
    bool use_texture_ = false;

   private:
    //RenderComponent() = default;
    void setup();
    void cleanup();

    RenderComponent() {
        program_ = BasicMeshShader();
        object_type = OTHER;
    }
};
#pragma once

#include <GL/glew.h>

#include <vector>

#include "core/TransformComponent.hpp"
#include "shader/PlayerTestShaderProgram.hpp"

class RenderComponent {
   public:
    RenderComponent(std::vector<glm::vec2>&& vertices);
    ~RenderComponent();

    void render(TransformComponent transform);

   private:
    void initializeShaders();
    void setupBuffers();
    void cleanupBuffers();
    std::vector<float> vertices() const;

    PlayerTestShaderProgram program;
    GLuint vao, vbo;
    std::vector<glm::vec2> verts;
};

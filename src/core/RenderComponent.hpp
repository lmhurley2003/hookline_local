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
    void set_visible(bool visible);

   private:
    std::vector<float> vertices() const;

    PlayerTestShaderProgram program_;
    bool visible_ = true;
    GLuint vao_, vbo_;
    std::vector<glm::vec2> verts_;
};

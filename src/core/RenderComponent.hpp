#pragma once

#include <GL/glew.h>

#include <vector>

#include "core/TransformComponent.hpp"
#include "shader/PlayerTestShaderProgram.hpp"

// TODO: For some reason passing a constructed RenderComponent is broken
// to entt.emplace<RenderComponent>(entity, RenderComponent(...)) and leads to
// no rendering ---> bad copy/move constructor, just don't use that or add a
// move constructor here

class RenderComponent {
   public:
    RenderComponent() = delete;
    RenderComponent(std::vector<glm::vec2>&& vertices, bool visible = true);
    ~RenderComponent();

    void render(TransformComponent transform);
    void set_visible(bool visible);

   private:
    std::vector<float> vertices() const;

    PlayerTestShaderProgram program_;
    GLuint vao_, vbo_;
    std::vector<glm::vec2> verts_;
    bool visible_;
};

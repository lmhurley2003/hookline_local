#include "RenderComponent.hpp"

#include "core/TransformComponent.hpp"

RenderComponent::RenderComponent(std::vector<glm::vec2>&& vertices)
    : vao(0), vbo(0) {
    verts = std::move(vertices);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
}

RenderComponent::~RenderComponent() {
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void RenderComponent::render(TransformComponent transform) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, verts.size() * sizeof(verts[0]), verts.data(),
                 GL_STATIC_DRAW);

    glBindVertexArray(vao);
    glVertexAttribPointer(program.position_loc, 2, GL_FLOAT, GL_FALSE, 0,
                          nullptr);
    glEnableVertexAttribArray(program.position_loc);

    glUseProgram(program.program);

    // Set uniforms
    glUniform2f(program.u_position_loc, transform.position.x,
                transform.position.y);
    glUniform2f(program.u_scale_loc, transform.scale.x, transform.scale.y);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, verts.size());

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
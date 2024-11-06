#include "RenderSystem.hpp"

#include <entt/entt.hpp>

#include "core/RenderComponent.hpp"
#include "core/TransformComponent.hpp"

void RenderSystem::render(glm::uvec2 drawable_size,
                          const entt::registry &registry) {
    (void)drawable_size;
    auto view = registry.view<TransformComponent, RenderComponent>();
    // Render each renderable
    for (const auto [entity, transform, renderable] : view.each()) {
        if (!renderable.visible_) {
            continue;
        }

        GLuint vao_ = renderable.vao_;
        GLuint vbo_ = renderable.vbo_;
        const auto &verts_ = renderable.verts_;
        const auto &program_ = renderable.program_;

        glBindBuffer(GL_ARRAY_BUFFER, vbo_);
        glBufferData(GL_ARRAY_BUFFER, verts_.size() * sizeof(verts_[0]),
                     verts_.data(), GL_STATIC_DRAW);

        glBindVertexArray(vao_);
        glVertexAttribPointer(program_.position_loc, 2, GL_FLOAT, GL_FALSE, 0,
                              nullptr);
        glEnableVertexAttribArray(program_.position_loc);

        glUseProgram(program_.program);

        // Set uniforms
        glUniform2f(program_.u_position_loc, transform.position.x,
                    transform.position.y);
        glUniform2f(program_.u_scale_loc, transform.scale.x, transform.scale.y);
        glUniform1f(program_.u_rotation_loc, transform.rotation);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, verts_.size());

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
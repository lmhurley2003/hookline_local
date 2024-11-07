/**
 * @file PlayerTestShaderProgram.hpp
 *
 * Temporary GL shader program for a basic character for demo (just a black
 * square right now). Change Header only for simplicity.
 */

#pragma once

#include <GL/glew.h>

struct PlayerTestShaderProgram {
    PlayerTestShaderProgram();
    ~PlayerTestShaderProgram();

    // Cannot copy a shader program
    PlayerTestShaderProgram(const PlayerTestShaderProgram& other) = delete;
    PlayerTestShaderProgram& operator=(const PlayerTestShaderProgram& other) =
        delete;

    PlayerTestShaderProgram(PlayerTestShaderProgram&& other) noexcept;

    PlayerTestShaderProgram& operator=(
        PlayerTestShaderProgram&& other) noexcept;

    GLuint program = 0;

    // Attribute (per-vertex variable) locations
    GLuint a_position_loc = 0;
    GLuint a_texture_coord_loc = 0;
    GLuint a_color_loc = 0;

    // Uniform locations
    GLuint u_position_loc = 0;
    GLuint u_scale_loc = 0;
    GLuint u_rotation_loc = 0;
    GLuint u_camera_position_loc = 0;
    GLuint u_camera_viewport_size_loc = 0;
    GLuint u_camera_pixels_per_unit_loc = 0;
    //   -- Fragment shader
    GLuint u_frag_texture_loc = 0;
    GLuint u_frag_use_texture_loc = 0;
};
/**
 * @file PlayerTestShaderProgram.hpp
 *
 * Temporary GL shader program for a basic character for demo (just a black
 * square right now). Change Header only for simplicity.
 */

#pragma once

#include <GL/glew.h>

#include "util/gl_compile_program.hpp"

struct PlayerTestShaderProgram {
    PlayerTestShaderProgram() {
        glCreateShader(GL_VERTEX_SHADER);
        program = gl_compile_program(
            // vertex shader
            "#version 330\n"
            "in vec2 position;\n"
            "uniform vec2 u_position;\n"  // from transform
            "uniform vec2 u_scale;\n"     // from transform
            "void main() {\n"
            "   gl_Position = vec4(position * u_scale + u_position, 0.0, "
            "1.0);\n"
            "}\n",
            // fragment shader
            "#version 330\n"
            "out vec4 FragColor;\n"
            "void main() {\n"
            "   FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
            "}\n");

        position_loc = glGetAttribLocation(program, "position");
        u_position_loc = glGetUniformLocation(program, "u_position");
        u_scale_loc = glGetUniformLocation(program, "u_scale");
    }

    ~PlayerTestShaderProgram() { glDeleteProgram(program); }

    GLuint program = 0;

    // Attribute (per-vertex variable) locations
    GLuint position_loc = -1;

    // Uniform locations
    GLuint u_position_loc = -1;
    GLuint u_scale_loc = -1;
};
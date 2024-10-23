/**
 * @file PlayerTestShaderProgram.hpp
 *
 * Temporary GL shader program for a basic character for demo (just a black
 * square right now). Change Header only for simplicity.
 */

#include <GL/glew.h>

#include "util/gl_compile_program.hpp"

struct PlayerTestShaderProgram {
    PlayerTestShaderProgram() {
        glCreateShader(GL_VERTEX_SHADER);
        program = gl_compile_program(
            // vertex shader
            "#version 330\n"
            "in vec2 position;\n"
            "void main() {\n"
            "   gl_Position = vec4(position, 0.0, 1.0);\n"
            "}\n",
            // fragment shader
            "#version 330\n"
            "out vec4 FragColor;\n"
            "void main() {\n"
            "   FragColor = vec4(0.0, 0.0, 0.0, 1.0);\n"
            "}\n");
    }

    ~PlayerTestShaderProgram() { glDeleteProgram(program); }

    GLuint program = 0;

    // Attribute (per-vertex variable) locations
    GLuint position_vec2 = -1;
};
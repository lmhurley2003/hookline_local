#pragma once

#include <GL/glew.h>

#include <string>
#include <unordered_map>

class AssetManager {
   public:
    void load_texture(const std::string &name, const std::string &filename);
    GLuint get_texture(const std::string &name);

   private:
    std::unordered_map<std::string, GLuint> textures_;
};

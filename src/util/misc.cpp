#include "misc.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace hookline {
std::vector<glm::vec2> get_basic_shape_debug() {
    return {/*BL*/ {-1.0, -1.0}, /*BR*/ {1.0, -1.0},
            /*TL*/ {-1.0, 1.0}, /*TR*/ {1.0, 1.0}};
}
}  // namespace hookline
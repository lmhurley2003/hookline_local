#include "misc.hpp"

#include <glm/glm.hpp>
#include <vector>

namespace hookline {
std::vector<glm::vec2> get_basic_shape_debug() {
    return {/*BL*/ {-0.5, -0.5}, /*BR*/ {0.5, -0.5},
            /*TL*/ {-0.5, 0.5}, /*TR*/ {0.5, 0.5}};
}
}  // namespace hookline
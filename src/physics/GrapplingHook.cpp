#include "GrapplingHook.hpp"

#include <iostream>

#include "physics/util.hpp"

void GrapplingHookComponent::try_attach(glm::vec2 start_position,
                                        glm::vec2 target_position,
                                        entt::registry &registry) {
    if (attached) {
        return;
    }

    glm::vec2 hit_position;
    glm::vec2 direction = glm::normalize(target_position - start_position);
    std::vector<entt::entity> ignore_list = {user, self};
    if (hookline::raycast(start_position, direction, max_length, registry,
                          ignore_list, &hit_position)) {
        std::cout << "Attached grapple\n";
        attached = true;
        attached_position = hit_position;
    }
}

void GrapplingHookComponent::detach() {
    if (!attached) {
        return;
    }
    attached = false;
    std::cout << "Detached grapple\n";
}

GrapplingHookComponent::GrapplingHookComponent(entt::entity self_,
                                               entt::entity user_)
    : self(self_), user(user_) {}
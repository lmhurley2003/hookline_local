#include <entt/entt.hpp>
#include <glm/glm.hpp>

class CollectableSystem {
   public:
    void update(float dt, entt::registry &registry, entt::entity player);
    void spawn(entt::registry &registry, glm::vec2 position);
    void spawn_random(entt::registry &registry);
    void on_pickup(entt::registry &registry, entt::entity collectable);

    int score = 0;
};
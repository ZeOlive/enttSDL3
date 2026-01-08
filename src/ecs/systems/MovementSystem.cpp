#include "MovementSystem.h"
#include "../Components.h"

void MovementSystem::update(entt::registry& registry, float dt) {
    auto view = registry.view<Position, Velocity>();

    for (auto entity : view) {
        auto& pos = view.get<Position>(entity);
        auto& vel = view.get<Velocity>(entity);

        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
    }
}

#include "MovementSystem.h"
#include "ecs/Components.h"

void MovementSystem::update(entt::registry& registry, float dt) {
    auto view = registry.view<RenderRect, Velocity>();

    for (auto entity : view) {
        auto& rectComponent = view.get<RenderRect>(entity);
        auto& rect = rectComponent.rect;
        auto& vel = view.get<Velocity>(entity);

        rect.x += vel.x * dt;
        rect.y += vel.y * dt;
    }
}

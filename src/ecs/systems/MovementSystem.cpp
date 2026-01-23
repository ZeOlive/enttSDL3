#include "MovementSystem.h"
#include "ecs/Components.h"
#include <math.h>

void MovementSystem::update(entt::registry& registry, float dt) {
    auto view = registry.view<RenderRect, Velocity>();

    constexpr float BALL_BASE_SPEED = 300.0f;
    constexpr float BALL_SPEED_DECAY  = 4.0f;

    for (auto entity : view) {
        auto& rectComponent = view.get<RenderRect>(entity);
        auto& rect = rectComponent.rect;
        auto& vel = view.get<Velocity>(entity);

        rect.x += vel.x * dt;
        rect.y += vel.y * dt;

        // Speed decay for ball
        float speed = std::hypot(vel.x, vel.y);
        if (speed > 0.0001f) {
            float newSpeed = std::lerp(speed, BALL_BASE_SPEED, 1.0f - std::exp(-BALL_SPEED_DECAY * dt));

            float scale = newSpeed / speed;
            vel.x *= scale;
            vel.y *= scale;
        }
    }
}
#include "CollisionSystem.h"
#include "../ecs/Components.h"

void CollisionSystem::update(entt::registry& registry) {
    auto balls = registry.view<Ball, Position, Velocity>();
    auto paddles = registry.view<Paddle, Position, RenderRect>();

    for (auto ball : balls) {
        auto& ballPos = balls.get<Position>(ball);
        auto& ballVel = balls.get<Velocity>(ball);

        for (auto paddle : paddles) {
            auto& pPos = paddles.get<Position>(paddle);
            auto& rect = paddles.get<RenderRect>(paddle);

            bool hit =
                ballPos.x > pPos.x &&
                ballPos.x < pPos.x + rect.w &&
                ballPos.y > pPos.y &&
                ballPos.y < pPos.y + rect.h;

            if (hit) {
                ballVel.x *= -1.f;
            }
        }
    }
}
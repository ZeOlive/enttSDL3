#pragma once
#include "ecs/Components.h"
#include <entt/entt.hpp>

class CollisionSystem {

public:
    void update(entt::registry& registry);
private:
    static void clampPaddles(entt::registry& registry);
    static void ballCollision(entt::registry& registry);
    static void ballPaddleCollision(entt::registry& registry, RenderRect& ballRect, Velocity& ballVel);
    static void ballWallCollision(RenderRect& ballRect, Velocity& ballVel);
    static void bounceBall(Velocity& ballVel, const SDL_FRect& ballRect, const SDL_FRect& paddleRect);
    static bool intersects(const SDL_FRect& a, const SDL_FRect& b);
    static void collisionReset(RenderRect& ballRect, Velocity& ballVel);

    static constexpr float TOP_BOUND = 0.0f;
    static constexpr float BOTTOM_BOUND = 600.0f;
    static constexpr float LEFT_BOUND = 0.0f;
    static constexpr float RIGHT_BOUND = 800.0f;
};

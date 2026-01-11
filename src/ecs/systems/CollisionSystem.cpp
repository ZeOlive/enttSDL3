#include "CollisionSystem.h"
#include "ecs/Components.h"

static bool intersects(const SDL_FRect& a, const SDL_FRect& b)
{
    return !(a.x + a.w <= b.x ||
             b.x + b.w <= a.x ||
             a.y + a.h <= b.y ||
             b.y + b.h <= a.y);
}

void CollisionSystem::update(entt::registry& registry) {
    auto balls = registry.view<TagBall, Velocity, RenderRect>();
    auto paddles = registry.view<TagPaddle, RenderRect>();
    auto paddleLeft = registry.view<TagLeftPaddle, RenderRect>();
    auto paddleRight = registry.view<TagRightPaddle, RenderRect>();
    constexpr float TOP_BOUND = 0.0f;
    constexpr float BOTTOM_BOUND = 600.0f;

    // Check for paddle collisions with walls
    for (auto paddle : paddles) {
        auto& paddleRect = paddles.get<RenderRect>(paddle);

        if (paddleRect.rect.y < TOP_BOUND) {
            paddleRect.rect.y = TOP_BOUND;
        }
        if (paddleRect.rect.y + paddleRect.rect.h > BOTTOM_BOUND) {
            paddleRect.rect.y = BOTTOM_BOUND - paddleRect.rect.h;
        }
    }

    for (auto ball : balls) {
        auto& ballVel = balls.get<Velocity>(ball);
        auto& ballRect = balls.get<RenderRect>(ball);

        for (auto paddle : paddles) {
            auto& paddleRect = paddles.get<RenderRect>(paddle);

            if (intersects(ballRect.rect, paddleRect.rect)) {
                // Reverse horizontal direction
                ballVel.x = -ballVel.x;

                // Move ball slightly to prevent sticking
                if (ballVel.x > 0)
                    ballRect.rect.x = paddleRect.rect.x + paddleRect.rect.w;
                else
                    ballRect.rect.x = paddleRect.rect.x - ballRect.rect.w;
                
                break;
            }
        }

        // Check for ball collisions with walls
        if (ballRect.rect.y <= TOP_BOUND) {
            ballRect.rect.y = TOP_BOUND;
            ballVel.y = -ballVel.y;
        }

        if (ballRect.rect.y + ballRect.rect.h >= BOTTOM_BOUND) {
            ballRect.rect.y = BOTTOM_BOUND - ballRect.rect.h;
            ballVel.y = -ballVel.y;
        }
    }
}
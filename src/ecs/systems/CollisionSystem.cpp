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
    auto ballsView = registry.view<TagBall, Velocity, RenderRect>();
    auto paddlesView = registry.view<TagPaddle, RenderRect>();

    constexpr float TOP_BOUND = 0.0f;
    constexpr float BOTTOM_BOUND = 600.0f;
    constexpr float LEFT_BOUND = 0.0f;
    constexpr float RIGHT_BOUND = 800.0f;

    // Check for paddle collisions with walls
    for (auto paddleEntity : paddlesView) {
        auto& paddleRect = paddlesView.get<RenderRect>(paddleEntity);

        if (paddleRect.rect.y < TOP_BOUND) {
            paddleRect.rect.y = TOP_BOUND;
        }
        if (paddleRect.rect.y + paddleRect.rect.h > BOTTOM_BOUND) {
            paddleRect.rect.y = BOTTOM_BOUND - paddleRect.rect.h;
        }
    }

    for (auto ballEntity : ballsView) {
        auto& ballVel = ballsView.get<Velocity>(ballEntity);
        auto& ballRect = ballsView.get<RenderRect>(ballEntity);

        // Check for ball collisions with paddles
        // Check collision for ball in the left collision zone
        if (ballVel.x < 0) {
            auto paddleLeftView = registry.view<TagLeftPaddle, RenderRect>();
            
            for (auto paddleEntity : paddleLeftView) {
                auto& paddleLeftRect = paddleLeftView.get<RenderRect>(paddleEntity);

                if ((intersects(ballRect.rect, paddleLeftRect.rect))) {
                    ballRect.rect.x = paddleLeftRect.rect.x + ballRect.rect.w;
                    ballVel.x = std::abs(ballVel.x);
                    break;
                }
            }
        }
        else {
            auto paddleRightView = registry.view<TagRightPaddle, RenderRect>();
            for (auto paddleEntity : paddleRightView) {
                auto& paddleRightRect = paddleRightView.get<RenderRect>(paddleEntity);

                if ((intersects(ballRect.rect, paddleRightRect.rect))) {
                    ballRect.rect.x = paddleRightRect.rect.x - ballRect.rect.w;
                    ballVel.x = -std::abs(ballVel.x);
                    break;
                }
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
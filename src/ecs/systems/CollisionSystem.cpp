#include "CollisionSystem.h"
#include <numbers>

void CollisionSystem::update(entt::registry& registry) {

    clampPaddles(registry);
    ballCollision(registry);
}

void CollisionSystem::clampPaddles(entt::registry& registry) {
    
    auto paddlesView = registry.view<TagPaddle, RenderRect>();

    for (auto paddleEntity : paddlesView) {
        auto& paddleRect = paddlesView.get<RenderRect>(paddleEntity);

        if (paddleRect.rect.y < TOP_BOUND) {
            paddleRect.rect.y = TOP_BOUND;
        }
        if (paddleRect.rect.y + paddleRect.rect.h > BOTTOM_BOUND) {
            paddleRect.rect.y = BOTTOM_BOUND - paddleRect.rect.h;
        }
    }    
}

void CollisionSystem::ballCollision(entt::registry& registry) {
    auto ballsView = registry.view<TagBall, Velocity, RenderRect>();

    for (auto ballEntity : ballsView) {
        auto& ballVel = ballsView.get<Velocity>(ballEntity);
        auto& ballRect = ballsView.get<RenderRect>(ballEntity);

        ballPaddleCollision(registry, ballRect, ballVel);
        ballWallCollision(ballRect, ballVel);

    }
}

void CollisionSystem::ballPaddleCollision(entt::registry& registry, RenderRect& ballRect, Velocity& ballVel) {
        // Check collision for ball in the left collision zone
        if (ballVel.x < 0) {
            auto paddleLeftView = registry.view<TagLeftPaddle, RenderRect, Velocity>();
            
            for (auto paddleEntity : paddleLeftView) {
                auto& paddleLeftRect = paddleLeftView.get<RenderRect>(paddleEntity);
                auto& paddleLeftVel = paddleLeftView.get<Velocity>(paddleEntity);

                if ((intersects(ballRect.rect, paddleLeftRect.rect))) {
                    // Pushball out
                    ballRect.rect.x = paddleLeftRect.rect.x + ballRect.rect.w;
                    bounceBall(ballVel, ballRect.rect, paddleLeftRect.rect, paddleLeftVel);
                    ballVel.x = std::abs(ballVel.x);
                    break;
                }
            }
        }
        // Check collision for ball in the right collision zone
        else {
            auto paddleRightView = registry.view<TagRightPaddle, RenderRect, Velocity>();

            for (auto paddleEntity : paddleRightView) {
                auto& paddleRightRect = paddleRightView.get<RenderRect>(paddleEntity);
                auto& paddleRightVel = paddleRightView.get<Velocity>(paddleEntity);

                if ((intersects(ballRect.rect, paddleRightRect.rect))) {
                    ballRect.rect.x = paddleRightRect.rect.x - ballRect.rect.w;
                    bounceBall(ballVel, ballRect.rect, paddleRightRect.rect, paddleRightVel);
                    ballVel.x = -std::abs(ballVel.x);
                    break;
                }
            }
        }
}

bool CollisionSystem::intersects(const SDL_FRect& a, const SDL_FRect& b)
{
    return !(a.x + a.w <= b.x ||
             b.x + b.w <= a.x ||
             a.y + a.h <= b.y ||
             b.y + b.h <= a.y);
}

void CollisionSystem::bounceBall(Velocity& ballVel, const SDL_FRect& ballRect, const SDL_FRect& paddleRect, const Velocity& paddleVel) {
    float ballCenterY =  ballRect.y + ballRect.h * 0.5f;
    float paddleCenterY = paddleRect.y + paddleRect.h * 0.5f;
    float relativeY = (ballCenterY - paddleCenterY) / (paddleRect.h * 0.5f);

    relativeY = std::clamp(relativeY, -1.0f, 1.0f);

    constexpr float MAX_BOUNCE_ANGLE = 60.0f * (std::numbers::pi_v<float> / 180.0f);
    float bounceAngle = relativeY * MAX_BOUNCE_ANGLE;

    float speed = std::sqrt(ballVel.x * ballVel.x + ballVel.y * ballVel.y);
    ballVel.x = speed * std::cos(bounceAngle);
    ballVel.y = speed * std::sin(bounceAngle);

    // Spin effect
    ballVel.y += paddleVel.y * SPIN_FACTOR;
    ballVel.y = std::clamp(ballVel.y, -MAX_Y_SPEED, MAX_Y_SPEED);
}

void CollisionSystem::ballWallCollision(RenderRect& ballRect, Velocity& ballVel){
    
    if (ballRect.rect.y <= TOP_BOUND) {
        ballRect.rect.y = TOP_BOUND;
        ballVel.y = -ballVel.y;
    }
    else if (ballRect.rect.y + ballRect.rect.h >= BOTTOM_BOUND) {
        ballRect.rect.y = BOTTOM_BOUND - ballRect.rect.h;
        ballVel.y = -ballVel.y;
    }
    else if (ballRect.rect.x <= LEFT_BOUND) {
        collisionReset(ballRect, ballVel);
    }
    else if (ballRect.rect.x + ballRect.rect.w >= RIGHT_BOUND) {
        collisionReset(ballRect, ballVel);
    }
}

void CollisionSystem::collisionReset(RenderRect& ballRect, Velocity& ballVel) {
    ballRect.rect.x = 400.f;
    ballRect.rect.y = 300.f;
    ballVel.x = -300.f;
    ballVel.y = -300.f;
}

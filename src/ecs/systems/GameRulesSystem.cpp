#include "GameRulesSystem.h"
#include "ecs/Components.h"

void GameRulesSystem::update(entt::registry& registry) {

    auto goalView = registry.view<Goal>();
    auto scoreView = registry.view<Score>();
    auto& scoreEntity = *scoreView.begin();
    auto& score = scoreView.get<Score>(scoreEntity);

    constexpr float LEFT_GOAL  = 0.0f;
    constexpr float RIGHT_GOAL = 800.0f;

    for (auto goalEntity : goalView) {
        auto& goal = goalView.get<Goal>(goalEntity);

        if (goal.leftSide) {
            score.right++;
            if (!renderSystem.updateScoreTexture(score.right, false)) {
                SDL_Log("Failed to update right score texture");
            }
            resetBall(registry, false);
            registry.remove<Goal>(goalEntity);
        }
        else {
            score.left++;
            if (!renderSystem.updateScoreTexture(score.left, true)) {
                SDL_Log("Failed to update left score texture");
            }
            resetBall(registry, true);
            registry.remove<Goal>(goalEntity);
        } 
    }    
}

void GameRulesSystem::resetBall(entt::registry& registry, bool leftPoint) {

    auto ballsView = registry.view<TagBall, Velocity, RenderRect>();

    for (auto ballEntity : ballsView) {    

        auto& ballRect = registry.get<RenderRect>(ballEntity).rect;
        auto& ballVel = registry.get<Velocity>(ballEntity);

        ballRect.x = 400.0f - (ballRect.w / 2.0f);
        ballRect.y = 300.0f - (ballRect.h / 2.0f);

        ballVel.x = (leftPoint == true) ? +300 : -300;
        ballVel.y = ballVel.y * 0.5f;
    }
}
#include "GameRulesSystem.h"
#include "ecs/Components.h"

void GameRulesSystem::update(entt::registry& registry) {

    auto goalView = registry.view<Goal>();
    auto scoreLeftView = registry.view<TagLeft, ScoreNumber>();
    auto& scoreLeftEntity = *scoreLeftView.begin();
    auto& scoreLeft = scoreLeftView.get<ScoreNumber>(scoreLeftEntity);

    auto scoreRightView = registry.view<TagRight, ScoreNumber>();
    auto& scoreRightEntity = *scoreRightView.begin();
    auto& scoreRight = scoreRightView.get<ScoreNumber>(scoreRightEntity);

    constexpr float LEFT_GOAL  = 0.0f;
    constexpr float RIGHT_GOAL = 800.0f;

    for (auto goalEntity : goalView) {
        auto& goal = goalView.get<Goal>(goalEntity);

        if (goal.leftSide) {
            scoreRight.value++;
            resetBall(registry, false);
        }
        else {
            scoreLeft.value++;
            resetBall(registry, true);
        } 
    }

    if (scoreLeft.value > 9) {
        SDL_Log("Right Player Wins!");
        registry.clear();
    }
    else if (scoreRight.value > 9) {
        SDL_Log("Left Player Wins!");
        registry.clear();
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
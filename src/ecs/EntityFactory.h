#pragma once
#include <entt/entt.hpp>
#include "Components.h"

class EntityFactory {
public:
    explicit EntityFactory(entt::registry& registry) : m_registry(registry) {}

    entt::entity createPaddleLeft();
    entt::entity createPaddleRight();
    entt::entity createBall();
    entt::entity createScoreBoard();

    private:
        entt::registry& m_registry;
        constexpr static float paddleWidth = 20.f;
        constexpr static float paddleHeight = 100.f;
        constexpr static float ballSize = 16.f;
        constexpr static float scoreSize = 40.f;
        constexpr static SDL_FPoint ballStartPos = {400.f, 300.f};
        constexpr static SDL_FPoint paddleLeftPos = {50.f - paddleWidth, 250.f};
        constexpr static SDL_FPoint paddleRightPos = {750.f, 250.f};
        constexpr static SDL_FPoint scoreLeftPos = {200.f - scoreSize, 20.f};
        constexpr static SDL_FPoint scoreRightPos = {600.f, 20.f};

};
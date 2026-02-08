#include "EntityFactory.h"

entt::entity EntityFactory::createPaddleLeft() {
    auto player = m_registry.create();
    m_registry.emplace<RenderRect>(player, SDL_FRect{paddleLeftPos.x, paddleLeftPos.y, paddleWidth, paddleHeight});
    m_registry.emplace<Color>(player, SDL_Color{255,255,255,255});
    m_registry.emplace<Velocity>(player, 0.f, 0.f);
    m_registry.emplace<TagPlayer>(player);
    m_registry.emplace<TagPaddle>(player);
    m_registry.emplace<TagLeftPaddle>(player);

    return player;
}

entt::entity EntityFactory::createPaddleRight() {
    auto ai = m_registry.create();
    m_registry.emplace<RenderRect>(ai, SDL_FRect{paddleRightPos.x, paddleRightPos.y, paddleWidth, paddleHeight});
    m_registry.emplace<Color>(ai, SDL_Color{255,255,255,255});
    m_registry.emplace<Velocity>(ai, 0.f, 0.f);
    m_registry.emplace<TagAI>(ai);
    m_registry.emplace<TagPaddle>(ai);
    m_registry.emplace<TagRightPaddle>(ai);

    return ai;
}

entt::entity EntityFactory::createBall() {
    auto ball = m_registry.create();
    m_registry.emplace<RenderRect>(ball, SDL_FRect{ballStartPos.x, ballStartPos.y, ballSize, ballSize});
    m_registry.emplace<Color>(ball, SDL_Color{255,255,255,255});
    m_registry.emplace<Velocity>(ball, -300.f, -300.f);
    m_registry.emplace<TagBall>(ball);

    return ball;
}

entt::entity EntityFactory::createScoreBoard() {
    auto score = m_registry.create();
    m_registry.emplace<Score>(score, 0, 0);
    m_registry.emplace<Color>(score, SDL_Color{255,255,255,255});

    return score;
}
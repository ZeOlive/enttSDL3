#include "EntityFactory.h"

entt::entity EntityFactory::createPaddleLeft() {
    auto player = m_registry.create();
    m_registry.emplace<RenderRect>(player, SDL_FRect{paddleLeftPos.x, paddleLeftPos.y, paddleWidth, paddleHeight});
    m_registry.emplace<Color>(player, SDL_Color{255,255,255,255});
    m_registry.emplace<Velocity>(player, 0.f, 0.f);
    m_registry.emplace<TagPlayer>(player);
    m_registry.emplace<TagPaddle>(player);
    m_registry.emplace<TagLeft>(player);

    return player;
}

entt::entity EntityFactory::createPaddleRight() {
    auto ai = m_registry.create();
    m_registry.emplace<RenderRect>(ai, SDL_FRect{paddleRightPos.x, paddleRightPos.y, paddleWidth, paddleHeight});
    m_registry.emplace<Color>(ai, SDL_Color{255,255,255,255});
    m_registry.emplace<Velocity>(ai, 0.f, 0.f);
    m_registry.emplace<TagAI>(ai);
    m_registry.emplace<TagPaddle>(ai);
    m_registry.emplace<TagRight>(ai);

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
    
    auto scoreLeft = m_registry.create();
    m_registry.emplace<ScoreNumber>(scoreLeft, 0u, true);
    m_registry.emplace<Color>(scoreLeft, SDL_Color{0,0,0,255});
    m_registry.emplace<RenderRect>(scoreLeft, SDL_FRect{scoreLeftPos.x, scoreLeftPos.y, scoreSize, scoreSize});
    m_registry.emplace<Texture>(scoreLeft, Texture{nullptr});
    m_registry.emplace<TagLeft>(scoreLeft);

    auto scoreRight = m_registry.create();
    m_registry.emplace<ScoreNumber>(scoreRight, 0u, false);
    m_registry.emplace<Color>(scoreRight, SDL_Color{0,0,0,255});
    m_registry.emplace<RenderRect>(scoreRight, SDL_FRect{scoreRightPos.x, scoreRightPos.y, scoreSize, scoreSize});
    m_registry.emplace<Texture>(scoreRight, Texture{nullptr});
    m_registry.emplace<TagRight>(scoreRight);

    return scoreLeft;
}
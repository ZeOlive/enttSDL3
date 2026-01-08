#include "EntityFactory.h"

entt::entity EntityFactory::createPaddleLeft() {
    auto player = m_registry.create();
    m_registry.emplace<Position>(player, 30.f, 200.f);
    m_registry.emplace<Velocity>(player, 0.f, 0.f);
    m_registry.emplace<RenderRect>(player, 20.f, 100.f, SDL_Color{255,255,255,255});
    m_registry.emplace<TagPaddle>(player);
    m_registry.emplace<TagPlayer>(player);

    return player;
}

entt::entity EntityFactory::createPaddleRight() {
    auto ai = m_registry.create();
    m_registry.emplace<Position>(ai, 750.f, 200.f);
    m_registry.emplace<Velocity>(ai, 0.f, 0.f);
    m_registry.emplace<RenderRect>(ai, 20.f, 100.f, SDL_Color{255,255,255,255});
    m_registry.emplace<TagPaddle>(ai);
    m_registry.emplace<TagAI>(ai);

    return ai;
}

entt::entity EntityFactory::createBall() {
    auto ball = m_registry.create();
    m_registry.emplace<Position>(ball, 400.f, 300.f);
    m_registry.emplace<Velocity>(ball, 300.f, 200.f);
    m_registry.emplace<RenderRect>(ball, 16.f, 16.f, SDL_Color{255,255,255,255});
    m_registry.emplace<TagBall>(ball);

    return ball;
}

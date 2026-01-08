#include "EntityFactory.h"
#include "Components.h"
#include "Tags.h"

void EntityFactory::createPaddles(entt::registry& registry) {
    auto player = registry.create();
    registry.emplace<Position>(player, 30.f, 200.f);
    registry.emplace<Velocity>(player);
    registry.emplace<Paddle>(player, 400.f);
    registry.emplace<PlayerTag>(player);
    registry.emplace<RenderRect>(player, 20.f, 100.f, SDL_Color{255,255,255,255});

    auto ai = registry.create();
    registry.emplace<Position>(ai, 750.f, 200.f);
    registry.emplace<Velocity>(ai);
    registry.emplace<Paddle>(ai, 300.f);
    registry.emplace<AITag>(ai);
    registry.emplace<RenderRect>(ai, 20.f, 100.f, SDL_Color{255,255,255,255});
}

void EntityFactory::createBall(entt::registry& registry) {
    auto ball = registry.create();
    registry.emplace<Position>(ball, 400.f, 300.f);
    registry.emplace<Velocity>(ball, 300.f, 200.f);
    registry.emplace<Ball>(ball, 8.f);
    registry.emplace<RenderRect>(ball, 16.f, 16.f, SDL_Color{255,255,255,255});
}

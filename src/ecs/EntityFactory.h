#pragma once
#include <entt/entt.hpp>

class EntityFactory {
public:
    static void createPaddles(entt::registry& registry);
    static void createBall(entt::registry& registry);
};
#pragma once
#include <entt/entt.hpp>

class GameRulesSystem {
public:
    void update(entt::registry& registry);

private:
    void resetBall(entt::registry& registry, bool leftPoint);
};
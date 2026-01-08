#pragma once
#include <entt/entt.hpp>

class InputSystem {
public:
    void update(entt::registry& registry, float dt);
};
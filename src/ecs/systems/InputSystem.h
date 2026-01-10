#pragma once
#include <entt/entt.hpp>
#include "InputState.h"

class InputSystem {
public:
    bool update(entt::registry& registry, const InputState& inputState);
};
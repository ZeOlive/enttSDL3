#include "InputSystem.h"
#include "ecs/Components.h"

bool InputSystem::update(entt::registry& registry, const InputState& inputState) {

    auto view = registry.view<TagPlayer, Velocity, Paddle>();

    for (auto entity : view) {
        auto& vel = view.get<Velocity>(entity);
        vel.y = 0.0f;

        if (inputState.up)   vel.y -= 300.0f;
        if (inputState.down) vel.y += 300.0f;
    }

    return true;
}
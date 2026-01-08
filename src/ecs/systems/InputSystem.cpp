#include "InputSystem.h"
#include "../Components.h"
#include "../Tags.h"
#include <SDL3/SDL.h>

void InputSystem::update(entt::registry& registry, float dt) {
    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    auto view = registry.view<PlayerTag, Velocity, Paddle>();
    for (auto entity : view) {
        auto& vel = view.get<Velocity>(entity);
        auto& paddle = view.get<Paddle>(entity);

        vel.y = 0.f;
        if (keys[SDL_SCANCODE_W]) vel.y = -paddle.speed;
        if (keys[SDL_SCANCODE_S]) vel.y =  paddle.speed;
    }
}
#pragma once
#include <entt/entt.hpp>
#include <SDL3/SDL.h>

class RenderSystem {
public:
    explicit RenderSystem(SDL_Renderer* renderer);

    bool draw(entt::registry& registry);

private:
    SDL_Renderer* m_renderer;
};

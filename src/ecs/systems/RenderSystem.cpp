#include "RenderSystem.h"
#include "ecs/Components.h"

bool RenderSystem::draw(entt::registry& registry) {
   
    auto view = registry.view<Position, RenderRect>();

    //SDL_Log("Renderable entities (hint): %zu", view.size_hint());

    // 1️⃣ Clear first (background color)
    if(!SDL_SetRenderDrawColor(&m_renderer, 0, 0, 0, 0))
        return false;
    if(!SDL_RenderClear(&m_renderer))
        return false;

    // 2️⃣ Draw entities
    for (auto entity : view) {
        const auto& pos  = view.get<Position>(entity);
        const auto& rect = view.get<RenderRect>(entity);

        SDL_FRect sdlRect{
            pos.x,
            pos.y,
            rect.w,
            rect.h
        };

        if(!SDL_SetRenderDrawColor(
            &m_renderer,
            rect.color.r,
            rect.color.g,
            rect.color.b,
            rect.color.a
        ))
            return false;
            
        if(!SDL_RenderFillRect(&m_renderer, &sdlRect))
            return false;
    }

    // 3️⃣ Present once
    if(!SDL_RenderPresent(&m_renderer))
        return false;

    return true;
}

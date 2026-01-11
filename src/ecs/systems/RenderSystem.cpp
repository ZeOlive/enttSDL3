#include "RenderSystem.h"
#include "ecs/Components.h"

bool RenderSystem::draw(entt::registry& registry) {

    auto view = registry.view<RenderRect, Color>();

    //SDL_Log("Renderable entities (hint): %zu", view.size_hint());

    // 1️⃣ Clear first (background color)
    if(!SDL_SetRenderDrawColor(&m_renderer, 0, 0, 0, 0))
        return false;
    if(!SDL_RenderClear(&m_renderer))
        return false;

    // 2️⃣ Draw entities
    for (auto entity : view) {
        const auto& rectComponent = view.get<RenderRect>(entity);
        const auto& colorComponent = view.get<Color>(entity);

        if(!SDL_SetRenderDrawColor(
            &m_renderer,
            colorComponent.color.r,
            colorComponent.color.g,
            colorComponent.color.b,
            colorComponent.color.a
        ))
            return false;

        if(!SDL_RenderFillRect(&m_renderer, &rectComponent.rect))
            return false;
    }

    // 3️⃣ Present once
    if(!SDL_RenderPresent(&m_renderer))
        return false;

    return true;
}

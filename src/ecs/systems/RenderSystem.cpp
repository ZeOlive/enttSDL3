#include "RenderSystem.h"
#include "ecs/Components.h"

bool RenderSystem::draw(entt::registry& registry) {

    //SDL_Log("Renderable entities (hint): %zu", view.size_hint());

    // Clear first (background color)
    if(!SDL_SetRenderDrawColor(&m_renderer, 0, 0, 0, 0))
        return false;
    if(!SDL_RenderClear(&m_renderer))
        return false;

    drawBallPaddles(registry);  // balls, paddles
    drawScore();                // score textures already prepared

    // Present once
    if(!SDL_RenderPresent(&m_renderer))
        return false;

    return true;
}

bool RenderSystem::drawBallPaddles(entt::registry& registry) {
    auto view = registry.view<RenderRect, Color>();

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

    return true;
}

bool RenderSystem::drawScore() {

    if (!m_leftScore.texture || !m_rightScore.texture){
        SDL_Log("Score textures not initialized");
        return false;
    }

    if (!SDL_RenderTexture(m_renderer, m_leftScore.texture, nullptr, &m_leftScore.dst)){
        SDL_Log("SDL_RenderTexture left score failed: %s", SDL_GetError());
        return false;
    }

    if (!SDL_RenderTexture(m_renderer, m_rightScore.texture, nullptr, &m_rightScore.dst)){
        SDL_Log("SDL_RenderTexture right score failed: %s", SDL_GetError());
        return false;
    }

    return true;
}

bool RenderSystem::updateScoreTexture(const uint scoreNumber, bool left) {

    Score& currentScore = left ? m_leftScore : m_rightScore;

    if (scoreNumber == currentScore.lastValue)
        return true; // No update needed

    if (currentScore.texture) {
        SDL_DestroyTexture(currentScore.texture);
        currentScore.texture = nullptr;
    }

    SDL_Color white{255, 255, 255, 255};
    std::string text = std::to_string(scoreNumber);
    SDL_Surface* surface = TTF_RenderText_Blended(m_font, text.c_str(), white);
    
    if (!surface) {
        SDL_Log("Failed to create surface for score: %s", TTF_GetError());
        return false;
    }

    currentScore.texture = SDL_CreateTextureFromSurface(m_renderer, surface);

    if (!currentScore.texture) {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        SDL_FreeSurface(surface);
        return;
    }

    currentScore.dst = {400.f, 20.f, static_cast<float>(surface->w), static_cast<float>(surface->h)};

    SDL_DestroySurface(surface);
    currentScore.lastValue = scoreNumber;
}
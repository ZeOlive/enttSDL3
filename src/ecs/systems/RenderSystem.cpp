#include "RenderSystem.h"
#include "ecs/Components.h"

void RenderSystem::init(entt::registry& registry) {

    auto scoreLeftView = registry.view<ScoreNumber, Texture, RenderRect, TagLeft>();
    auto& scoreLeftEntity = *scoreLeftView.begin();
    auto& scoreLeftTexture = scoreLeftView.get<Texture>(scoreLeftEntity).texture;
    auto& scoreLeftRect = scoreLeftView.get<RenderRect>(scoreLeftEntity).rect;

    auto scoreRightView = registry.view<ScoreNumber, Texture, RenderRect, TagRight>();
    auto& scoreRightEntity = *scoreRightView.begin();
    auto& scoreRightTexture = scoreRightView.get<Texture>(scoreRightEntity).texture;
    auto& scoreRightRect = scoreRightView.get<RenderRect>(scoreRightEntity).rect;

    updateScoreTexture(scoreLeftTexture, 0);
    updateScoreTexture(scoreRightTexture, 0);
}

bool RenderSystem::draw(entt::registry& registry) {

    //SDL_Log("Renderable entities (hint): %zu", view.size_hint());

    // Clear first (background color)
    if(!SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 0))
        return false;
    if(!SDL_RenderClear(m_renderer))
        return false;

    drawBallPaddles(registry);  // balls, paddles
    drawScore(registry);                // score textures already prepared

    // Present once
    if(!SDL_RenderPresent(m_renderer))
        return false;

    return true;
}

bool RenderSystem::drawBallPaddles(entt::registry& registry) {
    auto view = registry.view<RenderRect, Color>();

    for (auto entity : view) {
        const auto& rectComponent = view.get<RenderRect>(entity);
        const auto& colorComponent = view.get<Color>(entity);

        if(!SDL_SetRenderDrawColor(
            m_renderer,
            colorComponent.color.r,
            colorComponent.color.g,
            colorComponent.color.b,
            colorComponent.color.a
        ))
            return false;

        if(!SDL_RenderFillRect(m_renderer, &rectComponent.rect))
            return false;
    }

    return true;
}

bool RenderSystem::drawScore(entt::registry& registry) {

    auto scoreLeftView = registry.view<ScoreNumber, Texture, RenderRect, TagLeft>();
    auto& scoreLeftEntity = *scoreLeftView.begin();
    auto& scoreLeftTexture = scoreLeftView.get<Texture>(scoreLeftEntity).texture;
    auto& scoreLeftRect = scoreLeftView.get<RenderRect>(scoreLeftEntity).rect;

    auto scoreRightView = registry.view<ScoreNumber, Texture, RenderRect, TagRight>();
    auto& scoreRightEntity = *scoreRightView.begin();
    auto& scoreRightTexture = scoreRightView.get<Texture>(scoreRightEntity).texture;
    auto& scoreRightRect = scoreRightView.get<RenderRect>(scoreRightEntity).rect;

    // Check for goals and update score
    auto goalView = registry.view<Goal>();

    for (auto goalEntity : goalView) {
        auto& goal = goalView.get<Goal>(goalEntity);

        auto& scoreLeft = scoreLeftView.get<ScoreNumber>(scoreLeftEntity);
        auto& scoreRight = scoreRightView.get<ScoreNumber>(scoreRightEntity);

        if (goal.leftSide) {
            if (!updateScoreTexture(scoreLeftTexture, scoreRight.value)) {
                SDL_Log("SDL leftscore texture update failed: %s", SDL_GetError());
            }
        }
        else {
            if (!updateScoreTexture(scoreRightTexture, scoreLeft.value)) {
                SDL_Log("SDL rightscore texture update failed: %s", SDL_GetError());
            }
        }

        registry.remove<Goal>(goalEntity);
    }

    if (!SDL_RenderTexture(m_renderer, scoreLeftTexture, nullptr, &scoreLeftRect)){
        SDL_Log("SDL_RenderTexture left score failed: %s", SDL_GetError());
        return false;
    }

    if (!SDL_RenderTexture(m_renderer, scoreRightTexture, nullptr, &scoreRightRect)){
        SDL_Log("SDL_RenderTexture right score failed: %s", SDL_GetError());
        return false;
    }

    return true;
}

bool RenderSystem::updateScoreTexture(SDL_Texture*& scoreTexture, const unsigned int scoreValue) {

    if (scoreTexture) {
        SDL_DestroyTexture(scoreTexture);
        scoreTexture = nullptr;
    }

    SDL_Color white{255, 255, 255, 255};
    std::string text = std::to_string(scoreValue);
    SDL_Surface* surface = TTF_RenderText_Blended(m_font, text.c_str(), text.size(), white);
    
    if (!surface) {
        SDL_Log("Failed to create surface for score: %s", SDL_GetError());
        return false;
    }

    scoreTexture = SDL_CreateTextureFromSurface(m_renderer, surface);

    SDL_DestroySurface(surface);

    if (!scoreTexture) {
        SDL_Log("Failed to create texture from surface: %s", SDL_GetError());
        return false;
    }

    return true;
}
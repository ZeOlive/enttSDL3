#pragma once
#include <entt/entt.hpp>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

class RenderSystem {
public:
    explicit RenderSystem(SDL_Renderer* renderer)
        : m_renderer(renderer)
    {
        m_font = TTF_OpenFont("assets/Miss16Bit.ttf", 24);

        if (!m_font) {
            SDL_Log("Failed to load font: %s", SDL_GetError());
            throw std::runtime_error("Font load failed");
        }
    }

    ~RenderSystem() {
        if (m_font) {
            TTF_CloseFont(m_font);
        }
    }

    bool draw(entt::registry& registry);
    void init(entt::registry& registry);

private:
    bool updateScoreTexture(SDL_Texture*& scoreTexture, const unsigned int scoreValue);
    bool drawBallPaddles(entt::registry& registry);
    bool drawScore(entt::registry& registry);

    SDL_Renderer* m_renderer = nullptr;
    TTF_Font* m_font = nullptr;
};

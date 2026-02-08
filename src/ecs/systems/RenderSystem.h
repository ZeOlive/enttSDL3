#pragma once
#include <entt/entt.hpp>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

struct ScoreRenderData {
    SDL_Texture* texture = nullptr;
    SDL_FRect dst{};
    int lastValue = -1;
};

class RenderSystem {
public:
    explicit RenderSystem(SDL_Renderer& renderer) : m_renderer(renderer) {
        m_font = TTF_OpenFont("assets/SuperCorn.ttf", 24);
        if (!m_font) {
            SDL_Log("Failed to load font: %s", TTF_GetError());
        }
    };
    RenderSystem::~RenderSystem() {
        if (m_font) {
            TTF_CloseFont(m_font);
        }
    }
    bool draw(entt::registry& registry);
    bool updateScoreTexture(const uint scoreNumber, bool left);

private:
    void updateSingleScore(ScoreRenderData& data, int score, int x);
    bool drawBallPaddles(entt::registry& registry);
    bool drawScore();

    SDL_Renderer& m_renderer;
    TTF_Font* m_font = nullptr;
    ScoreRenderData m_leftScore;
    ScoreRenderData m_rightScore;

};

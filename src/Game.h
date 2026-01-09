#pragma once

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include <vector>
#include "ecs/Components.h"
#include "ecs/systems/RenderSystem.h"
#include "ecs/systems/MovementSystem.h"
#include "ecs/EntityFactory.h"

#define SDL_WINDOW_WIDTH 800
#define SDL_WINDOW_HEIGHT 600
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

class Game{
public:
    explicit Game(SDL_Renderer& renderer) : m_renderSystem(renderer) {};

	SDL_AppResult init();
	SDL_AppResult iterate();
	bool handleEvents();
	bool update(float dt);
	
private:
    entt::registry m_registry;
    RenderSystem m_renderSystem;
	MovementSystem m_movementSystem;
	uint64_t m_frameLast = 0;
};
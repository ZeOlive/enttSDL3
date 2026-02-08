#pragma once

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <entt/entt.hpp>
#include "InputState.h"
#include "ecs/systems/RenderSystem.h"
#include "ecs/systems/MovementSystem.h"
#include "ecs/systems/InputSystem.h"
#include "ecs/systems/CollisionSystem.h"
#include "ecs/systems/GameRulesSystem.h"

#define SDL_WINDOW_WIDTH 800
#define SDL_WINDOW_HEIGHT 600
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

class Game{
public:
    explicit Game(SDL_Renderer& renderer) : m_renderSystem(renderer) {};
	~Game() {
		TTF_Quit();
		SDL_Quit();
	}

	SDL_AppResult init();
	SDL_AppResult iterate();
	SDL_AppResult handleEvents(SDL_Event* event);
	bool update(float dt);
	
private:
    entt::registry m_registry;
	InputState m_inputState;
    RenderSystem m_renderSystem;
	MovementSystem m_movementSystem;
	CollisionSystem m_collisionSystem;
	GameRulesSystem m_gameRulesSystem;
	InputSystem m_inputSystem;
	uint64_t m_frameLast = 0;
};
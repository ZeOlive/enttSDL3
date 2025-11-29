#pragma once

#define SDL_MAIN_USE_CALLBACKS 1 /* use the callbacks instead of main() */
#include <SDL3/SDL.h>

#define SDL_WINDOW_WIDTH 800
#define SDL_WINDOW_HEIGHT 600
#define FPS 60
#define FRAME_TARGET_TIME (1000 / FPS)

class Game{
public:
	Game() = default;
	~Game() { clean(); }

	SDL_AppResult init();
	SDL_AppResult iterate();
	bool handleEvents();
	bool update();
	bool render();
	void clean();

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
};
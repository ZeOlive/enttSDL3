#include "Game.h"
#include <SDL3/SDL_main.h>
#include <entt/entt.hpp>

struct AppState {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    Game game;

    AppState(SDL_Renderer* r)
        : renderer(r)
        , game(r)
    {}
};

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]){
	SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Create a window and renderer for displaying graphics
    if (!SDL_CreateWindowAndRenderer("test/pong", SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, 0, &window, &renderer)) {
        return SDL_APP_FAILURE;
    }

    auto* state = new AppState(renderer);

    if (state->game.init() != SDL_APP_CONTINUE) {
        delete state;
        return SDL_APP_FAILURE;
	}

    *appstate = state;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate){
    auto* state = static_cast<AppState*>(appstate);
	return state->game.iterate();

}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event){
    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* appstate, SDL_AppResult result){
    auto* state = static_cast<AppState*>(appstate);

    SDL_DestroyRenderer(state->renderer);
    SDL_DestroyWindow(state->window);

    delete state;
}
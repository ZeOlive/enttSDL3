#include "Game.h"
#include <SDL3/SDL_main.h>

struct AppState {
    Game game;
};

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]){
	auto* state = new AppState();

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
    delete state;
}
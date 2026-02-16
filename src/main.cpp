#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "Game.h"

struct AppState {
    SDL_Window* window;
    SDL_Renderer* renderer;
    Game game;

    AppState(SDL_Window* w, SDL_Renderer* r): 
        window(w),
        renderer(r),
        game(r)
    {}

    ~AppState() {
        if (renderer) {
            SDL_DestroyRenderer(renderer);
            renderer = nullptr;
        }
        if (window) {
            SDL_DestroyWindow(window);
            window = nullptr;
        }
    }
}; 

SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[]){

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
        SDL_Log("SDL_Init failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_SetAppMetadata("Test Pong", "1.0", "com.example.Pong")) {
        return SDL_APP_FAILURE;
    }    

    if (!TTF_Init()) {
        SDL_Log("TTF_Init failed: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

	SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;

    // Create a window and renderer for displaying graphics
    if (!SDL_CreateWindowAndRenderer("test/pong", SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, 0, &window, &renderer)) {
        return SDL_APP_FAILURE;
    }

    auto* state = new AppState(window, renderer);
    state->game.init();
    
     *appstate = state;

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* appstate){
    auto* state = static_cast<AppState*>(appstate); 

	return state->game.iterate();

}

SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event){

    auto* state = static_cast<AppState*>(appstate);

    return state->game.handleEvents(event);
}

void SDL_AppQuit(void* appstate, SDL_AppResult result){
    auto* state = static_cast<AppState*>(appstate);

    delete state;

	SDL_Quit();
}
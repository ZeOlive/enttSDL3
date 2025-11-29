#include "Game.h"
#include <vector>

// This function iterates through a frame of the game loop.
SDL_AppResult Game::iterate()
{
    // Record the start time for the current frame.
    uint64_t frameStart = SDL_GetTicks();
	int frameTime = 0;

    if (!handleEvents())
    // Handle events
    if (!handleEvents())
		return SDL_APP_FAILURE;
    // Update game state
	if (!update())
		return SDL_APP_FAILURE;
    // Render the updated game state
    if (!render())
        return SDL_APP_FAILURE;

    // Calculate how long it took to handle, update and render the frame.
    frameTime = SDL_GetTicks() - frameStart;

    // If the frame was processed faster than our target frame time,
    // wait for the remaining time to ensure we hit the desired frame rate.
    if (FRAME_TARGET_TIME > frameTime)
    {
        SDL_Delay(FRAME_TARGET_TIME - frameTime);
    }

    return SDL_APP_CONTINUE;
}

// This function handles events such as input and window state changes.
// Currently, it always returns true indicating no issues with event handling.
bool Game::handleEvents()
{
    return true;
}

// This function initializes the game, sets up metadata, initializes SDL,
// creates a window and renderer for rendering graphics.
SDL_AppResult Game::init()
{
    // Set application metadata
    if (!SDL_SetAppMetadata("Test Pong", "1.0", "com.example.Pong")) {
        return SDL_APP_FAILURE;
    }

    // Initialize the necessary subsystems of SDL (video and joystick)
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    // Create a window and renderer for displaying graphics
    if (!SDL_CreateWindowAndRenderer("test/pong", SDL_WINDOW_WIDTH, SDL_WINDOW_HEIGHT, 0, &window, &renderer)) {
        return SDL_APP_FAILURE;
    }


    return SDL_APP_CONTINUE; // Successful initialization
}

// This function updates the game state. Currently, it does nothing and always returns true.
bool Game::update()
{
    return true;

}

// This function renders the current game state to the screen.
// It cycles through different colors for rendering each frame.
bool Game::render()
{
    static int i = 0;




    SDL_SetRenderDrawColor(renderer, 0, 0, i, SDL_ALPHA_OPAQUE); // Set render color
    i++; // Increment color value
    if (i > 255) i = 0; // Reset to start of colors

    // Clear the screen with the current render color
    SDL_RenderClear(renderer);

    // Present the rendered frame to the display
    SDL_RenderPresent(renderer);
    return true;
}

// This function cleans up and releases resources used by the game.
void Game::clean()
{


    // Destroy the renderer
    SDL_DestroyRenderer(renderer);
    // Destroy the window
    SDL_DestroyWindow(window);
}

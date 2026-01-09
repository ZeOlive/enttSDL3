#include "Game.h"

// This function iterates through a frame of the game loop.
SDL_AppResult Game::iterate()
{
    // Record the start time for the current frame.
    uint64_t frameStart = SDL_GetTicks();
	uint64_t frameTime = 0;
    // delta time
    float dt = static_cast<float>(frameStart - m_frameLast) * 0.001f;
    // limit dt to avoid big jumps
    m_frameLast = frameStart;
    dt = std::min(dt, 0.05f);

    // Handle events
    if (!handleEvents())
		return SDL_APP_FAILURE;
    // Update game state
	if (!update(dt))
		return SDL_APP_FAILURE;
    // Render the updated game state
    if (!m_renderSystem.draw(m_registry))
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

    EntityFactory factory(m_registry);

    factory.createBall();
    factory.createPaddleLeft();
    factory.createPaddleRight();

    m_frameLast = SDL_GetTicks();

    return SDL_APP_CONTINUE; // Successful initialization
}

// This function updates the game state. Currently, it does nothing and always returns true.
bool Game::update(float dt)
{
    m_movementSystem.update(m_registry, dt);

    return true;
}

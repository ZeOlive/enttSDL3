#include "Game.h"
//#include "ecs/Components.h"
#include "ecs/EntityFactory.h"

// This function iterates through a frame of the game loop.
SDL_AppResult Game::iterate(){
    // Record the start time for the current frame.
    uint64_t frameStart = SDL_GetTicks();
	uint64_t frameTime = 0;
    // delta time
    float dt = static_cast<float>(frameStart - m_frameLast) * 0.001f;
    // limit dt to avoid big jumps
    m_frameLast = frameStart;
    dt = std::min(dt, 0.05f);

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

SDL_AppResult Game::handleEvents(SDL_Event* event)
{
    switch (event->type) {
        case SDL_EVENT_QUIT:
            return SDL_APP_SUCCESS;
        case SDL_EVENT_KEY_DOWN:
        case SDL_EVENT_KEY_UP:
            if (event->key.key == 'w') {
                m_inputState.up = !(event->type-SDL_EVENT_KEY_DOWN);
            }
            else if (event->key.key == 's') {
                m_inputState.down = !(event->type-SDL_EVENT_KEY_DOWN);
            }
            break;
        default:
            break;
    }

    return SDL_APP_CONTINUE;
}

// This function initializes the game, sets up metadata, initializes SDL,
bool Game::init(){

    EntityFactory factory(m_registry);

    factory.createBall();
    factory.createPaddleLeft();
    factory.createPaddleRight();
    factory.createScoreBoard();

    m_renderSystem.init(m_registry);

    m_frameLast = SDL_GetTicks();

    return true; // Successful initialization
}

bool Game::update(float dt)
{
    m_inputSystem.update(m_registry, m_inputState);
    m_movementSystem.update(m_registry, dt);
    m_collisionSystem.update(m_registry);
    m_gameRulesSystem.update(m_registry);

    return true;
}

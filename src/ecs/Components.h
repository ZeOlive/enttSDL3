#pragma once
#include <SDL3/SDL.h>

struct Position {
    float x{};
    float y{};
};

struct Velocity {
    float x{};
    float y{};
};

struct Paddle {
    float speed{};
};

struct Ball {
    float radius{};
};

struct RenderRect {
    float w{};
    float h{};
    SDL_Color color{};
};

//Tags
struct TagPaddle {};
struct TagBall {};
struct TagPlayer {};
struct TagAI {};

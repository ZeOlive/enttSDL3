#pragma once
#include <SDL3/SDL.h>

struct RenderRect {
    SDL_FRect rect{};
};

struct Velocity {
    float x{};
    float y{};
};

struct Color {
    SDL_Color color{};
};

struct Paddle {
    float speed{};
};

struct Ball {
    float radius{};
};

struct Score {
    int left{};
    int right{};
};

struct Goal{
    bool leftSide{};
};

//Tags
struct TagBall {};
struct TagPaddle {};
struct TagLeftPaddle {}; // Player 1
struct TagRightPaddle {}; // Player 2
struct TagPlayer {};
struct TagAI {};

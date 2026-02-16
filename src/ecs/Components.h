#pragma once
#include <SDL3/SDL.h>

struct RenderRect {
    SDL_FRect rect{};
};

struct Texture {
    SDL_Texture* texture;
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

struct ScoreNumber {
    unsigned int value{};
    bool isLeft{};
};

struct Goal{
    bool leftSide{};
};

//Tags
struct TagBall {};
struct TagPaddle {};
struct TagRight {};
struct TagLeft {};
struct TagPlayer {};
struct TagAI {};

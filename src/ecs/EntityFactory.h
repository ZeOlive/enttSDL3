#pragma once
#include <entt/entt.hpp>
#include "Components.h"

class EntityFactory {
public:
    explicit EntityFactory(entt::registry& registry) : m_registry(registry) {}

    entt::entity createPaddleLeft();
    entt::entity createPaddleRight();
    entt::entity createBall();

    private:
        entt::registry& m_registry;
};
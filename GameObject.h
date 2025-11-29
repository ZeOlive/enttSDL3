#pragma once
class GameObject {
public:
    GameObject() = default;
    virtual ~GameObject() = default;

    virtual void update() = 0;
    virtual void draw() const = 0;
};


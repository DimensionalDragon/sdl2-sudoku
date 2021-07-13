#include "Mouse.hpp"

Mouse::Mouse()
{
    SDL_GetMouseState(&x, &y);
}

int Mouse::getX()
{
    SDL_GetMouseState(&x, &y);
    return x;
}

int Mouse::getY()
{
    SDL_GetMouseState(&x, &y);
    return y;
}

Vector2f Mouse::getPos()
{
    SDL_GetMouseState(&x, &y);
    return Vector2f(x, y);
}

bool Mouse::isInsideSquare(Square& square)
{
    Vector2f currentPos = getPos();
    return
    (currentPos.x >= square.getPosition().x && currentPos.x <= square.getPosition().x + square.getWidth()
    && currentPos.y >= square.getPosition().y && currentPos.y <= square.getPosition().y + square.getHeight());
}
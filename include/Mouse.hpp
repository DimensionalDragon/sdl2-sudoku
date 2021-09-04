#pragma once

#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "Util/Vector2f.hpp"
#include "Square.hpp"

class Mouse
{
public:
    Mouse();
    int getX();
    int getY();
    Vector2f getPos();
    bool isInsideEntity(Entity& entity);
private:
    int x, y;
};
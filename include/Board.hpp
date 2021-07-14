#pragma once

#include<vector>

#include "Util/Vector2f.hpp"
#include "Mouse.hpp"
#include "Square.hpp"

class Board
{
public:
    Board(Vector2f pStartPoint, SDL_Texture* pTexture);
    void resize(float newSize);
    void select(Mouse& mouse);
    void update(Mouse& mouse);
    Vector2f& getStartPoint();
    std::vector<Square>& getSquares();
    float getSquareSize();
    void setAllSquareColor(int r, int g, int b, int a);
private:
    std::vector<Square> squares;
    Vector2f startPoint;
    float squareSize;
};
#include<iostream>
#include<vector>

#include "Util/Vector2f.hpp"
#include "Mouse.hpp"
#include "Square.hpp"
#include "Board.hpp"

Board::Board(Vector2f pStartPoint, SDL_Texture* pTexture)
{
    startPoint = pStartPoint;
    squareSize = 40;
    squares.resize(81);
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            squares[9 * i + j] = Square(Vector2f(startPoint + Vector2f(j * squareSize, i * squareSize)), i, j, pTexture);
        }
    }
    for(Square& s : squares)
    {
        s.generateRelatives(squares);
    }
}

void Board::resize(float newSize)
{
    squareSize = newSize;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            squares[9 * i + j].setSize(newSize);
            squares[9 * i + j].setPosition(startPoint.x + j * newSize, startPoint.y + i * newSize);
        }
    }
}

void Board::select(Mouse& mouse)
{
    for(Square& s : squares)
    {
        if(mouse.isInsideSquare(s))
        {
            for(Square& other : squares)
            {
                other.deselect();
            }
            s.select();
        }
    }
}

void Board::update(Mouse& mouse)
{
    for(Square& s : squares)
    {
        if(mouse.isInsideSquare(s))
        {
            if(s.getColor()[0] != 147 && s.getColor()[0] != 112)
                s.setColor(165, 165, 165, 255);
            for(Square* r : s.getRelatives())
            {
                if(r->getColor()[0] != 147 && r->getColor()[0] != 112)
                    r->setColor(200, 200, 200, 255);
            }
        }
        if(s.isSelected())
        {
            s.setColor(112, 163, 214, 255);
            for(Square* r : s.getRelatives())
            {
                r->setColor(147, 198, 249, 255);
            }
        }
        //s.setTexture(numberTextures[s.getValue()]);
    }
}

Vector2f& Board::getStartPoint()
{
    return startPoint;
}

std::vector<Square>& Board::getSquares()
{
    return squares;
}

float Board::getSquareSize()
{
    return squareSize;
}

void Board::setAllSquareColor(int r, int g, int b, int a)
{
    for(Square& s : squares)
    {
        s.setColor(r, g, b, a);
    }
}
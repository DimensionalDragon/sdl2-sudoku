#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

#include "Util/Vector2f.hpp"
#include "Mouse.hpp"
#include "Square.hpp"
#include "Board.hpp"

Board::Board(Vector2f pStartPoint, std::vector<SDL_Texture*>& pSquareTextures)
{
    const std::vector<std::string> chosenProblem = generateProblem();
    for(int i = 0; i < 81; i++)
    {
        std::cout << chosenProblem[1].at(i);
        if(i % 3 == 2) std::cout << " ";
        if(i % 9 == 8) std::cout << std::endl;
        if(i % 27 == 26) std::cout << std::endl;
    }
    startPoint = pStartPoint;
    squareSize = 40;
    squares.resize(81);
    squareTextures.assign(pSquareTextures.begin(), pSquareTextures.end());
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            squares[9 * i + j] = Square(Vector2f(startPoint + Vector2f(j * squareSize, i * squareSize)), i, j, chosenProblem[0].at(9 * i + j) - '0', chosenProblem[1].at(9 * i + j) - '0', squareTextures[chosenProblem[0].at(9 * i + j) - '0']);
        }
    }
    for(Square& s : squares)
    {
        s.generateRelatives(squares);
    }
}

std::vector<std::string> Board::generateProblem()
{
    const int random = (rand() % 1000) + 1;
    std::string chosenLine;
    std::vector<std::string> chosenProblem;
    std::ifstream problemData("res/dev/sudoku.csv");
    for(int i = 1; std::getline(problemData, chosenLine); i++)
    {
        if(i == random) break;
    }
    std::stringstream chosenLineSS(chosenLine);
    while(chosenLineSS.good())
    {
        std::string temp;
        std::getline(chosenLineSS, temp, ',');
        chosenProblem.push_back(temp);
    }
    return chosenProblem;
}

void Board::resize(Vector2f pStartPoint, float newSize)
{
    startPoint = pStartPoint;
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
    bool noSquareSelected = true;
    for(Square& s : squares)
    {
        if(mouse.isInsideSquare(s))
        {
            for(Square& other : squares)
            {
                other.deselect();
            }
            s.select();
            noSquareSelected = false;
        }
    }
    if(noSquareSelected)
    {
        for(Square& s : squares)
        {
            s.deselect();
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
        s.setTexture(squareTextures[s.getValue()]);
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

void Board::setSelectedSquareValue(char key)
{
    if(key == '\b' || (key >= '1' && key <= '9'))
    {
        for(Square& s : squares)
        {
            if(s.isSelected()) s.writePen((key == '\b') ? 0 : key - '0');
        }
    }
}
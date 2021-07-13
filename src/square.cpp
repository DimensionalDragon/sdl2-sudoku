#include<iostream>
#include<vector>

#include "Util/Vector2f.hpp"
#include "Square.hpp"

Square::Square(Vector2f pPos, int pRow, int pColumn, SDL_Texture* pTexture)
    : Entity(pPos, 40, 40, pTexture)
{
    row = pRow;
    groupRow = row / 3;
    column = pColumn;
    groupColumn = column / 3;
    value = 0;
    selected = false;
    color.fill(255);
    pencil.fill(false);
    relatives.fill(nullptr);
}

void Square::generateRelatives(std::vector<Square>& squares)
{
    int counter = 0;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(!(i == row && j == column))
            {
                if(i == row || j == column)
                {
                    relatives[counter] = &squares[9 * i + j];
                    counter++;
                }
                else if(squares[9 * i + j].getGroupRow() == groupRow && squares[9 * i + j].getGroupColumn() == groupColumn)
                {
                    relatives[counter] = &squares[9 * i + j];
                    counter++;
                }
            }
        }
    }
}

void Square::select()
{
    selected = true;
}

void Square::deselect()
{
    selected = false;
}

int Square::getValue()
{
    return value;
}

int Square::getRow()
{
    return row;
}

int Square::getColumn()
{
    return column;
}

int Square::getGroupRow()
{
    return groupRow;
}

int Square::getGroupColumn()
{
    return groupColumn;
}

std::array<int, 4>& Square::getColor()
{
    return color;
}

std::array<Square*, 20> Square::getRelatives()
{
    return relatives;
}

bool Square::isSelected()
{
    return selected;
}

void Square::setTexture(SDL_Texture* pTexture)
{
    texture = pTexture;
}

void Square::setSize(float pSize)
{
    width = pSize;
    height = pSize;
}

void Square::setColor(int r, int g, int b, int a)
{
    color[0] = r;
    color[1] = g;
    color[2] = b;
    color[3] = a;
}

void Square::writePen(int pValue)
{
    pencil.fill(false);
    value = pValue;
}

void Square::writePencil(int pValue)
{
    pencil[pValue - 1] = !pencil[pValue -1];
}
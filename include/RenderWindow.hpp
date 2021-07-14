#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "Entity.hpp"
#include "Square.hpp"
#include "Board.hpp"

class RenderWindow
{
public:
    RenderWindow(const char* title, int width, int height);
    SDL_Texture* loadTexture(const char* filePath);
    int getRefreshRate();
    int getWidth();
    int getHeight();
    void updateSize();
    void clean();
    void clearScreen();
    void renderBox(Vector2f position, float width, float height);
    void render(Entity& entity);
    void render(Square& square);
    void render(Board& board);
    void display();
    
private:
    SDL_Window* window;
    int windowWidth, windowHeight;
    SDL_Renderer* renderer;
};
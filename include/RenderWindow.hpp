#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

#include "Entity.hpp"

class RenderWindow
{
public:
    RenderWindow(const char* title, int width, int height);
    SDL_Texture* loadTexture(const char* filePath);
    int getRefreshRate();
    int getWidth();
    int getHeight();
    void clean();
    void clearScreen();
    void render(Entity& entity);
    void display();
    
private:
    SDL_Window* window;
    int windowWidth, windowHeight;
    SDL_Renderer* renderer;
};
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>

#include "RenderWindow.hpp"
#include "Entity.hpp"

RenderWindow::RenderWindow(const char* title, int width, int height)
    :window(NULL), renderer(NULL)
{
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
    if(window == NULL) std::cout << "[ERROR] NULL Window: " << SDL_GetError() << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    windowHeight = height;
    windowWidth = width; 
}

SDL_Texture* RenderWindow::loadTexture(const char* filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);
    if(texture == NULL) std::cout << "[ERROR] Texture Load Failed: " << SDL_GetError() << std::endl;
    return texture;
}

int RenderWindow::getRefreshRate()
{
    int displayIndex = SDL_GetWindowDisplayIndex(window);
    SDL_DisplayMode mode;
    SDL_GetDisplayMode(displayIndex, 0, &mode);
    return mode.refresh_rate;
}

int RenderWindow::getWidth()
{
    return windowWidth;
}

int RenderWindow::getHeight()
{
    return windowHeight;
}

void RenderWindow::clean()
{
    SDL_DestroyWindow(window);
}

void RenderWindow::clearScreen()
{
    SDL_RenderClear(renderer);
}

void RenderWindow::render(Entity& entity)
{
    SDL_Rect src;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;
    src.w = entity.getCurrentFrame().w;
    src.h = entity.getCurrentFrame().h;

    SDL_Rect dest;
    dest.x = entity.getPosition().x;
    dest.y = entity.getPosition().y;
    dest.w = entity.getWidth();
    dest.h = entity.getHeight();

    SDL_RenderCopy(renderer, entity.getTexture(), &src, &dest);
}

void RenderWindow::display()
{
    SDL_RenderPresent(renderer);
}
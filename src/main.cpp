#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>

#include "RenderWindow.hpp"
#include "Entity.hpp"
#include "Util/Vector2f.hpp"

#define RANDOM_ZERO_TO_ONE 0.5 * (SDL_sinf(rand()) + 1)
#define NUMBER_OF_PARTICLES 250

int main(int argc, char *argv[])
{
    //SDL Init
    if(SDL_Init(SDL_INIT_EVERYTHING) > 0) std::cout << "[ERROR] Failed Init: " << SDL_GetError() << std::endl;
    if(!IMG_Init(IMG_INIT_PNG)) std::cout << "[ERROR] Failed Image Init: " << SDL_GetError() << std::endl;
    
    //Window and loading textures
    RenderWindow window("Particle Collision Sim v1.0", 1280, 720);

    std::vector<SDL_Texture*> entityTextures;

    entityTextures.push_back(window.loadTexture("res/images/circle_yellow.png"));

    //Particles container
    std::vector<Entity> entities;
    entities.push_back(Entity(Vector2f(0,0), 10, 10, entityTextures[0]));

    //Program starts
    bool isRunning = true;

    SDL_Event event;

    //Program loop
    while(isRunning)
    {
        int startTick = SDL_GetTicks();

        //Event handler
        while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_QUIT) isRunning = false;
        }

        window.clearScreen();

        window.render(entities[0]);

        window.display();

        //Timestep management
        int frameTicks = SDL_GetTicks() - startTick;
        if(frameTicks < 1000 / window.getRefreshRate())
            SDL_Delay(1000 / window.getRefreshRate() - frameTicks);
    }

    window.clean();
    SDL_Quit();

    return 0;
}

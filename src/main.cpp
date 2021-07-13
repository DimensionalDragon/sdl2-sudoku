#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>
#include<iostream>
#include<utility>
#include<algorithm>
#include<vector>

#include "RenderWindow.hpp"
#include "Mouse.hpp"
#include "Entity.hpp"
#include "Square.hpp"
#include "Util/Vector2f.hpp"

#define WINDOW_WIDTH window.getWidth()
#define WINDOW_HEIGHT window.getHeight()
#define SQUARE_SIZE SDL_min(WINDOW_WIDTH / 12, WINDOW_HEIGHT / 18)
#define BOARD_START_X (WINDOW_WIDTH - 9 * SQUARE_SIZE) * 0.5
#define BOARD_START_Y 120

int main(int argc, char *argv[])
{
    //SDL Init
    if(SDL_Init(SDL_INIT_EVERYTHING) > 0) std::cout << "[ERROR] Failed Init: " << SDL_GetError() << std::endl;
    if(!IMG_Init(IMG_INIT_PNG)) std::cout << "[ERROR] Failed Image Init: " << SDL_GetError() << std::endl;
    
    //Window, background, and textures
    RenderWindow window("Sudoku", 480, 720);

    SDL_Texture* backgroundTexture = window.loadTexture("res/images/bg.png");
    Entity background(Vector2f(0, 0), window.getWidth(), window.getHeight(), backgroundTexture);

    std::vector<SDL_Texture*> numberTextures;

    numberTextures.push_back(window.loadTexture("res/images/blank.png"));
    numberTextures.push_back(window.loadTexture("res/images/number1.png"));
    numberTextures.push_back(window.loadTexture("res/images/number2.png"));
    numberTextures.push_back(window.loadTexture("res/images/number3.png"));
    numberTextures.push_back(window.loadTexture("res/images/number4.png"));
    numberTextures.push_back(window.loadTexture("res/images/number5.png"));
    numberTextures.push_back(window.loadTexture("res/images/number6.png"));
    numberTextures.push_back(window.loadTexture("res/images/number7.png"));
    numberTextures.push_back(window.loadTexture("res/images/number8.png"));
    numberTextures.push_back(window.loadTexture("res/images/number9.png"));

    //Square/tile container
    std::vector<Square> squares;
    for(int i = 0; i < 9; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            squares.push_back(Square(Vector2f(BOARD_START_X + j * SQUARE_SIZE, BOARD_START_Y + i * SQUARE_SIZE), i, j, numberTextures[0]));
        }
    }

    for(int g = 0; g < 81; g++)
    {
        squares[g].generateRelatives(squares);
    }

    //Program starts
    bool isRunning = true;

    Mouse mouse;
    SDL_Event event;

    //Program loop
    while(isRunning)
    {
        int startTick = SDL_GetTicks();

        //Event handler
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    isRunning = false;
                    break;
                
                case SDL_WINDOWEVENT:
                    if(event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                    {
                        window.updateSize();
                        background.setWidth(WINDOW_WIDTH);
                        background.setHeight(WINDOW_HEIGHT);
                        for(int i = 0; i < 9; i++)
                        {
                            for(int j = 0; j < 9; j++)
                            {
                                squares[9 * i + j].setSize(SQUARE_SIZE);
                                squares[9 * i + j].setPosition(BOARD_START_X + j * SQUARE_SIZE, BOARD_START_Y + i * SQUARE_SIZE);
                            }
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
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
                    break;

                default:
                    break;
            }
        }

        window.clearScreen();

        window.render(background);

        std::for_each(squares.begin(), squares.end(), [](Square& in) { in.setColor(255, 255, 255, 255); });

        for(Square& s : squares) //Logic
        {
            if(mouse.isInsideSquare(s))
            {
                s.setColor(165, 165, 165, 255);
                for(Square* r : s.getRelatives())
                {
                    r->setColor(200, 200, 200, 255);
                }
            }
            s.setTexture(numberTextures[s.getValue()]);
        }

        for(Square& s : squares) //Render
        {
            window.render(s);
        }

        for(int i = 0; i < 3; i++)
        {
            for(int j = 0; j < 3; j++)
            {
                window.renderBox(Vector2f(BOARD_START_X + j * 3 * SQUARE_SIZE, BOARD_START_Y + i * 3 * SQUARE_SIZE), 3 * SQUARE_SIZE, 3 * SQUARE_SIZE);
            }
        }

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

#include <iostream>
#include <SDL_image.h>
#include "Game.h"
#include "TextureManager.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    //initiliaze fullscreen flag
    int flags = 0;

    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    //attempt to initialize SDL
    //initialize sdl
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout<<"SDL init success\n";
        //if succeded create our window
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        //if the window creation succeded create our render
        if(m_pWindow != 0){ // window init success
            std::cout<<"Window creation success\n";
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if(m_pRenderer != 0){ //render init success
                std::cout<<"Renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
            } else {
                std::cout<<"Renderer init fail\n";
                return false; // render init fail
            }
        } else {
            std::cout<<"Window init fail\n";
            return false; // window init fail
        }
    } else {
        std::cout<<"SDL init fail\n";
        return false; // sdl not initialized
    }

    //initialize texture manager
    m_textureManager.load("assets/animate-alpha.png", "animate", m_pRenderer);

    //initialize our texture
    SDL_Surface* pTempSurface = IMG_Load("assets/animate-alpha.png");
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    //initialize rectangle
    //SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);
    m_sourceRectangle.w = 128;
    m_sourceRectangle.h = 82;
    m_destinationRectangle.x = 0;
    m_sourceRectangle.x = 0;
    m_destinationRectangle.y = 0;
    m_sourceRectangle.y = 0;
    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;

    std::cout<<"Init success\n";
    m_bRunning = true; //everything inited successfully, lets start the mainloop
    return true;
}

void Game::render(){
    SDL_RenderClear(m_pRenderer); //clear the render to the draw color
    m_textureManager.draw("animate", 0, 0, 128, 82, m_pRenderer);
    m_textureManager.drawFrame("animate", 100, 100, 128, 82, 1, m_currentFrame, m_pRenderer);
    /*Render with animation and without animation*/
    //SDL_RenderCopyEx(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle, (double)0, 0, SDL_FLIP_HORIZONTAL);
    //SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    SDL_RenderPresent(m_pRenderer); //draw to the scrren
}

void Game::handleEvents(){
    SDL_Event event;
    if(SDL_PollEvent(&event)){
        switch(event.type){
            case SDL_QUIT:
                m_bRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::clean(){
    std::cout<<"Cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::update(){
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    //m_sourceRectangle.x = int(((SDL_GetTicks() / 100) % 6));
}

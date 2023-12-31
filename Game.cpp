#include <iostream>
#include <SDL_image.h>
#include "Game.h"
#include "TextureManager.h"
#include "Player.h"
#include "InputHandler.h"
#include "MenuState.h"
#include "PlayState.h"

Game* Game::s_pInstance = 0;

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
    if(!TheTextureManager::Instance()->Instance()->load("assets/animate-alpha.png", "animate", m_pRenderer)){
        return false;
    }
    //another way without singleton
    //m_textureManager.load("assets/animate-alpha.png", "animate", m_pRenderer);
    m_gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));
    m_gameObjects.push_back(new Enemy(new LoaderParams(100, 300, 128, 82, "animate")));
    m_gameObjects.push_back(new SDLGameObject(new LoaderParams(100, 400, 128, 82, "animate")));

    //initialize Input Handler
    TheInputHandler::Instance()->initialiseJoysticks();

    //intialize fsm
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MenuState());

    std::cout<<"Init success\n";
    m_bRunning = true; //everything inited successfully, lets start the mainloop
    return true;
}

void Game::render(){
    SDL_RenderClear(m_pRenderer); //clear the render to the draw color
    /*for(std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++){
        m_gameObjects[i]->draw();
    }*/

    m_pGameStateMachine->render();

    //whithout inheritance
    //TheTextureManager::Instance()->draw("animate", 0, 0, 128, 82, m_pRenderer);
    //TheTextureManager::Instance()->drawFrame("animate", 100, 100, 128, 82, 1, m_currentFrame, m_pRenderer);

    //whitout singleton
    //m_textureManager.draw("animate", 0, 0, 128, 82, m_pRenderer);
    //m_textureManager.drawFrame("animate", 100, 100, 128, 82, 1, m_currentFrame, m_pRenderer);
    SDL_RenderPresent(m_pRenderer); //draw to the scrren
}

void Game::handleEvents(){
    TheInputHandler::Instance()->update();

    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RETURN)){
        m_pGameStateMachine->changeState(new PlayState());
    }
}

void Game::clean(){
    std::cout<<"Cleaning game\n";
    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

void Game::update(){
    m_pGameStateMachine->update();
    /*for(std::vector<GameObject*>::size_type i=0; i != m_gameObjects.size(); i++){
        m_gameObjects[i]->update();
    }*/
}


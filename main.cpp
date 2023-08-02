#include <exception>
#include <string>
#include <iostream>
#include <SDL.h>
#include "Game.h"

bool g_bRunning = true;

int main( int argc, char * argv[] ){
    std::cout<<"Game init attempt... \n";
    //std::cout<<TheGame::Instance();

    if(TheGame::Instance()->init("Chapter 1", 100, 100, 640, 480, false)){
        std::cout<<"Game init success\n";
        while(TheGame::Instance()->running()){
            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            SDL_Delay(10);
        }

    } else {
        std::cout<<"game init failure\n"<<SDL_GetError()<<"\n";
        return -1;
    }
    TheGame::Instance()->clean();
    return 0;
}

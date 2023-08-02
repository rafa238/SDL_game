#ifndef __Game__
#define __Game__

#include "SDL.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Game{
public:
    static Game* Instance(){
        if(s_pInstance == 0){
            s_pInstance = new Game();
            return s_pInstance;
        }
        return s_pInstance;
    }


    //simply set the running variable to true
    bool init(const char*, int, int, int, int, bool);
    void render();
    void update();
    void handleEvents();
    void clean();

    //a function to access the private running variable
    bool running(){return m_bRunning; }

    SDL_Renderer* getRenderer() const {return m_pRenderer; }

private:
    Game(){}
    ~Game(){}

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;

    //whithout singleton
    //TextureManager m_textureManager;

    std::vector<GameObject*> m_gameObjects;
    static Game* s_pInstance;
};

typedef Game TheGame;

#endif // __GAME__

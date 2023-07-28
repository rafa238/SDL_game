#ifndef __Game__
#define __Game__
#include "SDL.h"
class Game{
public:
    Game(){}
    ~Game(){}

    //simply set the running variable to true

    bool init(const char*, int, int, int, int, bool);
    void render();
    void update();
    void handleEvents();
    void clean();

    //a function to access the private running variable
    bool running(){return m_bRunning; }

private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    bool m_bRunning;
};

#endif // __GAME__

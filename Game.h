#include "SDL.h"
#include "TextureManager.h"
#ifndef __Game__
#define __Game__
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

    int m_currentFrame;
    TextureManager m_textureManager;

    SDL_Texture* m_pTexture; // the new sdl texture variable
    SDL_Rect m_sourceRectangle; // the first rectangle
    SDL_Rect m_destinationRectangle; //another rectangle
};

#endif // __GAME__

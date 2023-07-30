#include <string>
#include <map>
#include <SDL.h>
#ifndef __TEXTUREMANAGER__
#define __TEXTUREMANAGER__

class TextureManager{
public:
    TextureManager(){}
    ~TextureManager(){}
    std::map<std::string, SDL_Texture*> m_textureMap;

    bool load(std::string filename, std::string id, SDL_Renderer* pRenderer);
    //draw
    void draw(std::string id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
    //drawframe
    void drawFrame(std::string id, int x, int y, int width, int height, int currentRow, int currentFrame,
                    SDL_Renderer* pRenderer, SDL_RendererFlip flip=SDL_FLIP_NONE);

};

#endif // TEXTUREMANAGER

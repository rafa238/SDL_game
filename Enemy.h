#ifndef __ENEMY__
#define __ENEMY__
#include "SDLGameObject.h"

class Enemy : public SDLGameObject{
public:
    Enemy(const LoaderParams* pParams);
    //void load(int x, int y, int width, int height, std::string textureID);
    //void draw(SDL_Renderer* pRenderer);
    virtual void draw();
    virtual void update();
    virtual void clean();
};

#endif // __ENEMY__

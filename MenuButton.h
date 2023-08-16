#ifndef __MENUBUTTON__
#define __MENUBUTTON__
#include "SDLGameObject.h"
#include "InputHandler.h"

class MenuButton : public SDLGameObject{
public:
    MenuButton(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

private:
    enum button_state{
        MOUSE_OUT = 0,
        MOUSE_OVER = 1,
        CLICKED = 2
    };
};

#endif // MENUBUTTON_H_INCLUDED

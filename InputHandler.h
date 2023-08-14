#ifndef __INPUTHANDLER__
#define __INPUTHANDLER__
#include "SDL.h"
#include <vector>

class InputHandler{
public:
static InputHandler* Instance(){
    if(s_pInstance == 0){
        s_pInstance = new InputHandler();
    }

    return s_pInstance;
}
void update();
void clean();

void initialiseJoysticks();
bool joysticksInitilised(){
    return m_bJoysticksInitialised;
}

private:
    InputHandler(){}
    ~InputHandler(){}

    static InputHandler* s_pInstance;
    bool m_bJoysticksInitialised;
    std::vector<SDL_Joystick*> m_joysticks;
};

typedef InputHandler TheInputHandler;

#endif // __INPUTHANDLER__

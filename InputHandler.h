#ifndef __INPUTHANDLER__
#define __INPUTHANDLER__
#include "SDL.h"
#include <vector>
#include <utility>
#include "Vector2D.h"

class InputHandler{
public:
    //singleton instance
    static InputHandler* Instance(){
        if(s_pInstance == 0){
            s_pInstance = new InputHandler();
        }

        return s_pInstance;
    }

    //intialise joysticks
    void initialiseJoysticks();
    bool joysticksInitilised(){
        return m_bJoysticksInitialised;
    }
    void reset();

    //update and clean
    void update();
    void clean();

    bool getButtonState(int joy, int buttonNumber){
        return m_buttonStates[joy][buttonNumber];
    }

    bool getMouseButtonState(int buttonNumber){
        return m_mouseButtonStates[buttonNumber];
    }

    Vector2D* getMousePosition(){
        return m_mousePosition;
    }

    //keyboard event
    bool isKeyDown(SDL_Scancode key);

     // joystick events
    int getAxisX(int joy, int stick) const;
    int getAxisY(int joy, int stick) const;
    bool getButtonState(int joy, int buttonNumber) const;

    // mouse events
    enum mouse_buttons{
        LEFT = 0,
        MIDDLE = 1,
        RIGHT = 2
    };
    bool getMouseButtonState(int buttonNumber) const;
    Vector2D* getMousePosition() const;

    //helpers
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joysticksValues;
    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);

private:
    InputHandler();
    ~InputHandler();

    static InputHandler* s_pInstance;
    // handle keyboard events
    void onKeyDown();
    void onKeyUp();
    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);
    // handle joysticks events
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);

    //keyboard variables
    const Uint8* m_keystate;
    bool m_bJoysticksInitialised;

    //joysticks variables
    const int m_joystickDeadZone = 10000;
    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::vector<bool>> m_buttonStates;
    //mouse variables
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;


};

typedef InputHandler TheInputHandler;

#endif // __INPUTHANDLER__

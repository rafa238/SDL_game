#include "InputHandler.h"
#include "Game.h"
#include <SDL2/SDL.h>

InputHandler* InputHandler::s_pInstance = 0;
void InputHandler::initialiseJoysticks(){
    if(SDL_WasInit(SDL_INIT_JOYSTICK) == 0){
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if(SDL_NumJoysticks() > 0){
        for(int i=0; i < SDL_NumJoysticks(); i++){
            SDL_Joystick* joy = SDL_JoystickOpen(i);
            if(joy){
                m_joysticks.push_back(joy);
                m_joysticksValues.push_back(std::make_pair(new Vector2D(0,0), new Vector2D(0,0))); //add a pair

                std::vector<bool> tempButtons;

                for(int j=0; j<SDL_JoystickNumButtons(joy); j++){
                    tempButtons.push_back(false);
                }

                m_buttonStates.push_back(tempButtons);
            } else {
                std::cout<< SDL_GetError();
            }
        }

        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialised = true;
        std::cout << "Initialised " << m_joysticks.size() << " joysticks \n";
    } else {
        std::cout<<"No joysticks\n";
        m_bJoysticksInitialised = false;
    }

}

void InputHandler::clean(){
    if(m_bJoysticksInitialised){
        for(int i=0; i < SDL_NumJoysticks(); i++){
            SDL_JoystickClose(m_joysticks[i]);
        }
    }
}

void InputHandler::update(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if(event.type == SDL_QUIT){
            TheGame::Instance()->clean();
        }

        /*Mouse Events*/
        if(event.type == SDL_MOUSEBUTTONDOWN){
            if(event.button.button == SDL_BUTTON_LEFT){
                m_mouseButtonStates[LEFT] = true;
            }
            if(event.button.button == SDL_BUTTON_MIDDLE){
                m_mouseButtonStates[MIDDLE] = true;
            }
            if(event.button.button == SDL_BUTTON_RIGHT){
                m_mouseButtonStates[RIGHT] = true;
            }
        }

        if(event.type == SDL_MOUSEBUTTONUP){
            if(event.button.button == SDL_BUTTON_LEFT){
                m_mouseButtonStates[LEFT] = false;
            }
            if(event.button.button == SDL_BUTTON_MIDDLE){
                m_mouseButtonStates[MIDDLE] = false;
            }
            if(event.button.button == SDL_BUTTON_RIGHT){
                m_mouseButtonStates[RIGHT] = false;
            }
        }

        if(event.type == SDL_MOUSEMOTION){
            m_mousePosition->setX((float)event.motion.x);
            m_mousePosition->setY((float)event.motion.y);
        }

        /*Joystick events*/
        if(event.type == SDL_JOYBUTTONDOWN){
            int whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = true;
        }

        if(event.type == SDL_JOYBUTTONUP){
            int whichOne = event.jaxis.which;
            m_buttonStates[whichOne][event.jbutton.button] = false;
        }

        if(event.type == SDL_JOYAXISMOTION){
            int whichOne = event.jaxis.which;
            std::cout<<"event Value: " << event.jaxis.value<< " axis: "<<event.jaxis.axis<<" type: "<<event.jaxis.type <<"\n";
            //left stick move left or right
            if(event.jaxis.value == 0){
                std::cout<<"entro al axis 0 \n";
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joysticksValues[whichOne].first->setX(1);
                } else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joysticksValues[whichOne].first->setX(-1);
                } else {
                    m_joysticksValues[whichOne].first->setX(0);
                }
            }

            //left stick move up or down
            if(event.jaxis.value == 1){
                std::cout<<"Entro al axis 1\n";
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joysticksValues[whichOne].first->setY(1);
                } else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joysticksValues[whichOne].first->setY(-1);
                } else {
                    m_joysticksValues[whichOne].first->setY(0);
                }
            }

            //right stick move left or right
            if(event.jaxis.value == 3){
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joysticksValues[whichOne].second->setX(1);
                } else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joysticksValues[whichOne].second->setX(-1);
                } else {
                    m_joysticksValues[whichOne].second->setX(0);
                }
            }

            // right stick move up or down

            if(event.jaxis.value == 4){
                if(event.jaxis.value > m_joystickDeadZone){
                    m_joysticksValues[whichOne].second->setY(1);
                } else if(event.jaxis.value < -m_joystickDeadZone){
                    m_joysticksValues[whichOne].second->setY(-1);
                } else {
                    m_joysticksValues[whichOne].second->setY(0);
                }
            }

        }

    }
}

int InputHandler::xvalue(int joy, int stick){
    if(m_joysticksValues.size() > 0){
        if(stick == 1){
            return m_joysticksValues[joy].first->getX();
        } else if(stick == 2){
            return m_joysticksValues[joy].second->getX();
        }
    }
    return 0;
}


int InputHandler::yvalue(int joy, int stick){
    if(m_joysticksValues.size() > 0){
        if(stick == 1){
            return m_joysticksValues[joy].first->getY();
        } else if(stick == 2){
            return m_joysticksValues[joy].second->getY();
        }
    }
    return 0;
}

bool InputHandler::isKeyDown(SDL_Scancode key){
    if(m_keystate != 0){
        if(m_keystate[key] == 1){
            return true;
        } else {
            return false;
        }
    }
    return false;
}


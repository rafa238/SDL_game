#include "Player.h"
Player::Player(const LoaderParams* pParams):SDLGameObject(pParams){

}

void Player::draw(){
    SDLGameObject::draw();
}

void Player::update(){
    m_velocity.setX(0);
    m_velocity.setY(0);
    handleInput(); //input manager
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    SDLGameObject::update();
}

void Player::handleInput(){
    /*Button pressed*/
    /*
    if(TheInputHandler::Instance()->getButtonState(0, 3))
    {
        m_velocity.setX(1);
    }
    */
    //Mouse click
    /*if(TheInputHandler::Instance()->getMouseButtonState(InputHandler::mouse_buttons::LEFT)){
        m_velocity.setX(1);
    }*/
    //mouse motion
    /*Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
    m_velocity = (*vec - m_position) / 100;*/

    //keyboard
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT)){
        m_velocity.setX(2);
    }
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT)){
        m_velocity.setX(-2);
    }
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_UP)){
        m_velocity.setY(-2);
    }
    if(TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_DOWN)){
        m_velocity.setY(2);
    }

    //joystick
    if(TheInputHandler::Instance()->joysticksInitilised()){
        if(TheInputHandler::Instance()->xvalue(0, 1) > 0 ||
        TheInputHandler::Instance()->xvalue(0, 1) < 0){
            m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 1));
        }

        if(TheInputHandler::Instance()->yvalue(0, 1) > 0 ||
        TheInputHandler::Instance()->yvalue(0, 1) < 0){
            m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 1));
        }

        if(TheInputHandler::Instance()->xvalue(0, 2) > 0 ||
        TheInputHandler::Instance()->xvalue(0, 2) < 0){
            m_velocity.setX(1 * TheInputHandler::Instance()->xvalue(0, 2));
        }

        if(TheInputHandler::Instance()->yvalue(0, 2) > 0 ||
        TheInputHandler::Instance()->yvalue(0, 2) < 0){
            m_velocity.setY(1 * TheInputHandler::Instance()->yvalue(0, 2));
        }
    }
}

void Player::clean(){}

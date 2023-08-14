#include "SDLGameObject.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Game.h"
#include "Vector2D.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams):GameObject(pParams),
m_position(pParams->getX(), pParams->getY()),
m_velocity(0, 0), m_aceleration(0,0){
    //m_x = pParams->getX();
    //m_y = pParams->getY();
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();

    m_currentRow = 1;
    m_currentFrame = 1;
}

void SDLGameObject::draw(){
    //TextureManager::Instance()->drawFrame(m_textureID, m_x, m_y, m_width, m_height, m_currentRow, m_currentFrame, TheGame::Instance()->getRenderer());
    TextureManager::Instance()->drawFrame(m_textureID,
    (int)m_position.getX() , (int)m_position.getY(),
    m_width, m_height,
    m_currentRow, m_currentFrame,
    TheGame::Instance()->getRenderer());
}

void SDLGameObject::update(){
    m_velocity += m_aceleration;
    m_position += m_velocity;
    //m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

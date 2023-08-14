#include "Enemy.h"

/*void Enemy::load(int x, int y, int width, int height, std::string textureID){
    GameObject::load(x, y, width, height, textureID);
}*/

Enemy::Enemy(const LoaderParams* pParams):SDLGameObject(pParams){

}

void Enemy::draw(){
    //GameObject::draw(pRenderer);
    SDLGameObject::draw();
}

void Enemy::update(){
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
    m_velocity.setX(1);
    m_velocity.setY(1);
    SDLGameObject::update();
    //m_position.setX(m_position.getX() + 1);
    //m_position.setY(m_position.getY() + 1);
    //m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Enemy::clean(){}

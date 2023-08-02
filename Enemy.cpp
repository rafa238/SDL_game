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
    m_y += 1;
    m_x += 1;
    m_currentFrame = int(((SDL_GetTicks() / 100) % 6));
}

void Enemy::clean(){}

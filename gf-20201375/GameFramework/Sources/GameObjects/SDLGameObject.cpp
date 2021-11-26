#include "SDLGameObject.h"
#include "..\Game.h"
#include "..\TextureManager.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams), m_position(pParams->getX(), pParams->getY()), m_velocity(0, 0), m_acceleration(0, 0)
{
    m_x = pParams->getX();
    m_y = pParams->getY();
    m_width = pParams->getWidth();
    m_height = pParams->getHeight();
    m_textureID = pParams->getTextureID();
    m_currentRow = 0;
    m_currentFrame = 0;
    m_flipX = pParams->getFlipX();

    m_moveSpeed = 0;
    m_jumpSpeed = 0;

    m_isJumping = false;
    m_isGround = false;
    m_isObstacle = false;
}

void SDLGameObject::draw()
{
    /* TheTextureManager::Instance()
      ->drawFrame
          (
            m_textureID,
            (int)m_position.getX(), (int)m_position.getY(),
            m_width, m_height,
            m_currentRow, m_currentFrame,
            m_destRect,
            TheGame::Instance()->getRenderer(),
            m_flipX
          ); */

    TheTextureManager::Instance()
        ->drawFrame
        (
            m_textureID,
            m_position.getX() - TheGame::Instance()->getCameraRect().x,
            //m_position.getY() - TheGame::Instance()->getCameraRect().y,
            m_position.getY(),
            m_width, m_height,
            m_currentRow, m_currentFrame,
            m_destRect,
            TheGame::Instance()->getRenderer(),
            m_flipX
        );
}

void SDLGameObject::update()
{
    m_velocity += m_acceleration;
    m_position += m_velocity;
}

bool SDLGameObject::checkCollision(const SDL_Rect& target, int type)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = m_position.getX();
    rightA = leftA + m_width;
    topA = m_position.getY();
    bottomA = topA + m_height;

    leftB = target.x;
    rightB = target.x + target.w;
    topB = target.y;
    bottomB = target.y + target.h;

    if (bottomA < topB) // 아래 충돌?
        return false;

    if (topA > bottomB) // 위 충돌?
        return false;

    if (rightA < leftB) // 오른쪽 충돌?
        return false;

    if (leftA > rightB) // 왼쪽 충돌?
        return false;

    return true;
}

void SDLGameObject::clean()
{

}
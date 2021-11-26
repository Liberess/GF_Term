#include "Enemy.h"
#include "..\Game.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
    m_isHit = false;
}

void Enemy::draw()
{
    SDLGameObject::draw();
}

void Enemy::update()
{
    hit();

    move();

    checkCollision();

    SDLGameObject::update();

    m_currentFrame = (SDL_GetTicks() / 100) % 5;
}

void Enemy::move()
{
    static float currentVelocityY = 0;
    currentVelocityY += 0.02f * 9.8f;

    // If Grounded
    if (m_isGround)
    {
        m_velocity.setY(0);
        m_acceleration.setY(0);
        currentVelocityY = 0.0f;
    }
    else
    {
        m_velocity.setY(currentVelocityY);
    }
}

void Enemy::checkCollision()
{
    if (TheGame::Instance()->m_gameObjects["ground1"] != 0)
    {
        if (SDLGameObject::checkCollision(TheGame::Instance()->m_gameObjects["ground1"]->getDestRect()))
        {
            m_isGround = true;
        }
        else
        {
            m_isGround = false;
        }
    }
}

void Enemy::hit()
{
    if (!m_isHit)
        return;

    if (m_timer.done())
        m_currentRow = 0;
}

void Enemy::destroy()
{
    m_currentRow = 1;

    if (!m_isHit)
    {
        m_isHit = true;
        m_timer.setInterval(1000);
        m_timer.start();
        m_currentRow = 1;
        return;
    }

    //TheGame::Instance()->destroyGameObject("enemy");
}

void Enemy::clean()
{

}
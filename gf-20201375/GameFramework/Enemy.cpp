#include "Enemy.h"

Enemy::Enemy(const LoaderParams *pParams) : 
SDLGameObject(pParams)
{
	m_velocity.setX(0.001);
	m_velocity.setY(2);
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	m_numFrames = 5;
	m_currentFrame = int(((SDL_GetTicks() / 100) % m_numFrames));

	if (m_position.getY() < 0) {
		m_velocity.setY(2);
	}
	else if (m_position.getY() > 400) {
		m_velocity.setY(-2);
	}
	SDLGameObject::update();
}

void Enemy::clean()
{

}

void Enemy::handleInput()
{
	if (TheInputHandler::Instance()->getMouseButtonState(LEFT))
	{
		m_velocity.setX(1);
	}
	Vector2D* vec = TheInputHandler::Instance()->getMousePosition();
	m_velocity = (*vec - m_position) / 100;
}

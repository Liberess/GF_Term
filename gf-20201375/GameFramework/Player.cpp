#include "Player.h"
#include "Game.h"
#include "TextureManager.h"

Player::Player(const LoaderParams* pParams) :
	SDLGameObject(pParams)
{

}

void Player::draw()
{
	if (m_velocity.getX() > 0) // ¿À¸¥ÂÊ
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(),
			(Uint32)m_position.getY(),
			m_width, m_height,
			m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer(),
			SDL_FLIP_HORIZONTAL);
	}
	else // ¿ÞÂÊ
	{
		TextureManager::Instance()->drawFrame(m_textureID,
			(Uint32)m_position.getX(),
			(Uint32)m_position.getY(),
			m_width, m_height,
			m_currentRow, m_currentFrame,
			TheGame::Instance()->getRenderer());
	}

	m_currentFrame = int(((SDL_GetTicks() / 100) % 5));
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput();

	SDLGameObject::update();
}

void Player::clean()
{

}

void Player::handleInput()
{
	Vector2D* target = TheInputHandler::Instance()
		->getMousePosition();
	m_velocity = *target - m_position;
	m_velocity /= 50;

	if (TheInputHandler::Instance()
		->isKeyDown(SDL_SCANCODE_SPACE) == 1)
	{
		TheGame::Instance()->m_gameObjects.push_back(
			new Enemy(
				new LoaderParams(
					m_position.getX(), m_position.getY(),
					128, 82, "animate")
			)
		);
	}
}
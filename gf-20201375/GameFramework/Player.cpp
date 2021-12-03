#include "Player.h"
#include "Game.h"
#include "TextureManager.h"
#include "PlayState.h"

Player::Player(const LoaderParams* pParams) :
	SDLGameObject(pParams)
{
	m_flipX = SDL_FLIP_NONE;
}

void Player::draw()
{
	SDLGameObject::draw();

	m_currentFrame = int(((SDL_GetTicks() / 100) % 11));
}

void Player::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);

	handleInput(); // 이동 입력

	SDLGameObject::update();
}

void Player::clean()
{

}

void Player::handleInput()
{
	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		if (m_position.getX() + m_width < TheGame::Instance()->getScreenWidth())
		{
			m_velocity.setX(5);
			m_flipX = SDL_FLIP_NONE;
		}
		else
		{
			m_velocity.setX(0);
		}

		m_currentRow = 2; //Run
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		if (m_position.getX() > 0)
		{
			m_velocity.setX(-5);
			m_flipX = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			m_velocity.setX(0);
		}

		m_currentRow = 2; //Run
	}
	else
	{
		m_currentRow = 1; //Idle
		m_velocity.setX(0);
	}
}
#include "Player.h"
#include "Game.h"
#include "TextureManager.h"
#include "AudioManager.h"

Player::Player(const LoaderParams* pParams) :
	SDLGameObject(pParams)
{
	m_flipX = SDL_FLIP_NONE;

	m_velocity.setX(0);
	m_velocity.setY(0);
}

void Player::draw()
{
	SDLGameObject::draw();
	m_currentFrame = int(((SDL_GetTicks() / 100) % 11));
}

void Player::update()
{
	handleInput(); // Input Movement
	SDLGameObject::update();
}

void Player::clean() { delete this; }

void Player::handleInput()
{
	static int count = 0;
	static bool isWalking = false;

	if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_RIGHT))
	{
		isWalking = true;

		if (m_position.getX() + m_width < TheGame::Instance()->getScreenWidth())
		{
			m_velocity.setX(4);
			m_flipX = SDL_FLIP_NONE;
		}
		else
		{
			m_velocity.setX(0);
		}
	}
	else if (TheInputHandler::Instance()->isKeyDown(SDL_SCANCODE_LEFT))
	{
		isWalking = true;

		if (m_position.getX() > 0)
		{
			m_velocity.setX(-4);
			m_flipX = SDL_FLIP_HORIZONTAL;
		}
		else
		{
			m_velocity.setX(0);
		}
	}
	else
	{
		isWalking = false;

		m_velocity.setX(0);
	}

	if (isWalking)
	{
		m_currentRow = 2; //Run

		if(count == 0)
#ifdef WIN32
			TheAudioManager::Instance()->PlaySFX(SfxType::Move);
#endif // WIN32

		++count;
	}
	else
	{
		count = 0;
		m_currentRow = 1; //Idle
#ifdef WIN32
		TheAudioManager::Instance()->StopSFX(SfxType::Move);
#endif // WIN32
	}
}
#include "MenuButton.h"
#include "AudioManager.h"

MenuButton::MenuButton(const LoaderParams* pParams, void(*callback)())
	: SDLGameObject(pParams), m_callback(callback)
{
	m_bReleased = false;
}

void MenuButton::draw()
{
	SDLGameObject::draw();
}

void MenuButton::clean()
{
	SDLGameObject::clean();
}

void MenuButton::update()
{
	Vector2D* pMousePos =
				TheInputHandler::Instance()->getMousePosition();

	// 마우스 포인터 좌표의 x값이 메뉴버튼의 x값 시점부터 종점과
	// y값 시점부터 종점 사이에 있으면
	if (pMousePos->getX() < (m_position.getX() + m_width)
		&& pMousePos->getX() > m_position.getX()
		&& pMousePos->getY() < (m_position.getY() + m_height)
		&& pMousePos->getY() > m_position.getY())
	{
		if (TheInputHandler::Instance()->getMouseButtonState(LEFT) &&
			m_bReleased)
		{
			m_currentFrame = CLICKED;
			m_callback();
			m_bReleased = false;
#ifdef WIN32
			TheAudioManager::Instance()->PlaySFX(SfxType::BtnClick);
#endif
			SDL_Delay(200);
		}
		else if (!TheInputHandler::Instance()->getMouseButtonState(LEFT))
		{
			m_bReleased = true;
			m_currentFrame = MOUSE_OVER;
		}
	}
	else
	{
		m_currentFrame = MOUSE_OUT;
	}
}
#include "PauseState.h"
#include "Game.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "AudioManager.h"

const std::string PauseState::s_pauseID = "PAUSE";
PauseState *PauseState::s_pInstance = nullptr;

void PauseState::s_pauseToMain() // 메인 화면으로
{
	TheGame::Instance()->getStateMachine()->changeState(
		MenuState::Instance());
}

void PauseState::s_resumePlay() // 다시 플레이
{
	TheGame::Instance()->m_time = 0.0f;
	TheGame::Instance()->getStateMachine()->popState();
}

void PauseState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->update();
}

void PauseState::render()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->draw();
}

bool PauseState::onEnter() // 일시정지 상태
{
#ifdef WIN32
	TheAudioManager::Instance()->PauseBGM();
#endif // WIN32

	if (!TheTextureManager::Instance()->load("Assets/UI/resume.png",
		"resumebutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/UI/main.png",
		"mainbutton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	GameObject* button1 = new MenuButton(new
		LoaderParams(260, 150, 200, 80, "mainbutton"), s_pauseToMain);
	GameObject* button2 = new MenuButton(new
		LoaderParams(260, 250, 200, 80, "resumebutton"), s_resumePlay);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);
	std::cout << "entering PauseState" << std::endl;
	return true;
}

bool PauseState::onExit() // 일시정지 상태 해제
{
#ifdef WIN32
	TheAudioManager::Instance()->ResumeBGM();
#endif // WIN32

	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	TheTextureManager::Instance()
		->clearFromTextureMap("resumebutton");

	TheTextureManager::Instance()
		->clearFromTextureMap("mainbutton");

	std::cout << "exiting PauseState" << std::endl;
	return true;
}
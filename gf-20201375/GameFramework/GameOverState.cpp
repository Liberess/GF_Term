#include "GameOverState.h"
#include "TextManager.h"
#include "AudioManager.h"

const std::string GameOverState::s_gameOverID = "GAME OVER";
GameOverState* GameOverState::s_pInstance = nullptr;

void GameOverState::s_gameOverToMain()
{
	TheGame::Instance()->getStateMachine()->changeState(
		MenuState::Instance());
}

void GameOverState::s_restartPlay()
{
	TheGame::Instance()->getStateMachine()->changeState
	(PlayState::Instance());
}

bool GameOverState::onEnter()
{
#ifdef WIN32
	TheAudioManager::Instance()->StopBGM();
	TheAudioManager::Instance()->StopAllSFX();
#endif // WIN32

	if (!TheTextureManager::Instance()->load("Assets/UI/main.png",
		"mainButton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/UI/restart.png",
		"restart", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(260, 180,
		200, 80, "mainButton"), s_gameOverToMain);
	GameObject* button2 = new MenuButton(new LoaderParams(260, 280, 200,
		80, "restart"), s_restartPlay);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "Entering PauseSate" << std::endl;
	return true;
}

void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
		m_gameObjects[i]->update();
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
		m_gameObjects[i]->draw();

	SDL_Color color = { 255, 0, 0 };
	TheTextManager::Instance()->drawText(
		"Game Over", 182, 55, 80, color, TheGame::Instance()->getRenderer());
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	TheTextureManager::Instance()
		->clearFromTextureMap("mainButton");
	TheTextureManager::Instance()
		->clearFromTextureMap("restart");
	std::cout << "Exiting PauseState" << std::endl;

	TheGame::Instance()->m_time = 0.0f;

	return true;
}
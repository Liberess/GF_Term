#include "GameOverState.h"

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
	if (!TheTextureManager::Instance()->load("Assets/UI/gameover.png",
		"gameovertext", TheGame::Instance()->getRenderer()))
	{
		return false;
	}
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

	GameObject* gameOverText = new AnimatedGraphic(
		new LoaderParams(200, 100, 190, 30, "gameovertext"), 2);

	GameObject* button1 = new MenuButton(new LoaderParams(200, 200,
		200, 80, "mainButton"), s_gameOverToMain);

	GameObject* button2 = new MenuButton(new LoaderParams(200, 300, 200,
		80, "restart"), s_restartPlay);

	m_gameObjects.push_back(gameOverText);
	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	std::cout << "Entering PauseSate" << std::endl;
	return true;
}

void GameOverState::update()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->update();
	}
}

void GameOverState::render()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->draw();
	}
}

bool GameOverState::onExit()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->clean();
	}
	m_gameObjects.clear();

	TheTextureManager::Instance()
		->clearFromTextureMap("gameovertext");
	TheTextureManager::Instance()
		->clearFromTextureMap("mainButton");
	TheTextureManager::Instance()
		->clearFromTextureMap("restart");
	std::cout << "Exiting PauseState" << std::endl;

	return true;
}
#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObject.h"
#include "PauseState.h"
#include "GameStateMachine.h"
#include "GameOverState.h"
#include <iostream>

const std::string PlayState::s_playID = "PLAY";
PlayState *PlayState::s_pInstance  = nullptr;

void PlayState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->update();

	if (checkCollision(
		dynamic_cast<SDLGameObject*>(m_gameObjects[1]),
		dynamic_cast<SDLGameObject*>(m_gameObjects[2])))
	{
		TheGame::Instance()->getStateMachine()
			->changeState(GameOverState::Instance());
	}

	if (TheInputHandler::Instance()->isKeyDown(
		SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->
			changeState(PauseState::Instance());
	}
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
		m_gameObjects[i]->draw();
}

bool PlayState::onEnter()
{
	std::cout << "entering PlayState" << std::endl;

	if (!TheTextureManager::Instance()->load("Assets/platform.png",
		"platform", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("Assets/Ninja_Frog-export.png", 
	"player", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load(
		"Assets/poop-export.png", "poop",
		TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* platform = new Platform(
		new LoaderParams(0, 432, 720, 48, "platform"));
	m_gameObjects.push_back(platform);

	GameObject* player = new Player(
		new LoaderParams(328, 368, 64, 64, "player"));
	m_gameObjects.push_back(player);

	GameObject* poop1 = new Enemy(
		new LoaderParams(500, 300, 32, 32, "poop"));
	m_gameObjects.push_back(poop1);

	return true;
}

bool PlayState::onExit()
{
	std::cout << "exiting PlayState" << std::endl;

	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();
	TheTextureManager::Instance()->clearFromTextureMap("player");
	return true;
}

bool PlayState::checkCollision(SDLGameObject* p1, SDLGameObject* p2)
{
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	leftA = p1->getPosition().getX();
	rightA = p1->getPosition().getX() + p1->getWidth();
	topA = p1->getPosition().getY();
	bottomA = p1->getPosition().getY() + p1->getHeight();

	leftB = p2->getPosition().getX();
	rightB = p2->getPosition().getX() + p2->getWidth();
	topB = p2->getPosition().getY();
	bottomB = p2->getPosition().getY() + p2->getHeight();

	if (bottomA <= topB) { return false; }
	if (topA >= bottomB) { return false; }
	if (rightA <= leftB) { return false; }
	if (leftA >= rightB) { return false; }

	return true;
}
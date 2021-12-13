#include "PlayState.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObject.h"
#include "PauseState.h"
#include "GameStateMachine.h"
#include "GameOverState.h"
#include "TextManager.h"
#include "AudioManager.h"
#include <iostream>
#include <cmath>
#include <cstring>

const std::string PlayState::s_playID = "PLAY";
PlayState *PlayState::s_pInstance  = nullptr;

void PlayState::update()
{
	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->update();

	for (int i = 5; i < m_gameObjects.size(); i++) // CheckCollision
	{
		if (checkCollision(
			dynamic_cast<SDLGameObject*>(m_gameObjects[4]),	// Player
			dynamic_cast<SDLGameObject*>(m_gameObjects[i])))	// Poop
		{
			TheGame::Instance()->getStateMachine()		   // If CheckCollision == true,
				->changeState(GameOverState::Instance()); // Player Die (GameOver)

#ifdef WIN32
			TheAudioManager::Instance()->PlaySFX(SfxType::GameOver);
#endif
		}
	}

	if (TheInputHandler::Instance()->isKeyDown( // Pause Panel
		SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->getStateMachine()->
			changeState(PauseState::Instance());
	}

	TheGame::Instance()->m_time += 0.01f;
}

void PlayState::render()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
		m_gameObjects[i]->draw();

	// Time Unit Change
	int second = (int)floor(TheGame::Instance()->m_time);
	int minute = second / 60;
	second = second % 60;

	// Set Time Text
	std::string a = (minute < 10) ? "0" + std::to_string(minute) : std::to_string(minute);
	std::string b = " : ";
	std::string c = (second < 10) ? "0" + std::to_string(second) : std::to_string(second);
	std::string d = a + b + c;

	char ch[100] = "";
	strcpy(ch, d.c_str());

	// Draw Time Text UI
	SDL_Color color = { 0, 0, 0 };
	TheTextManager::Instance()->drawText(
		ch, 10, 10, 25, color, TheGame::Instance()->getRenderer());
}

bool PlayState::onEnter()
{
	std::cout << "entering PlayState" << std::endl;

	if (!TheTextureManager::Instance()->load("Assets/background.jpg",
		"background", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

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

	if (!TheTextureManager::Instance()->load("Assets/poop-export.png",
		"poop", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("Assets/Cloud-export.png",
		"cloud1", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	if (!TheTextureManager::Instance()->load("Assets/Cloud.png",
		"cloud2", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* background = new Platform(
		new LoaderParams(0, 0, 720, 480, "background"));
	m_gameObjects.push_back(background);

	GameObject* platform = new Platform(
		new LoaderParams(0, 432, 720, 48, "platform"));
	m_gameObjects.push_back(platform);

	GameObject* cloud1 = new Cloud(
		new LoaderParams(0, 80, 64, 64, "cloud1"));
	m_gameObjects.push_back(cloud1);

	GameObject* cloud2 = new Cloud(
		new LoaderParams(0, 20, 32, 32, "cloud2"));
	m_gameObjects.push_back(cloud2);

	GameObject* player = new Player(
		new LoaderParams(328, 368, 64, 64, "player"));
	m_gameObjects.push_back(player);

	int xPos = -10;
	for (int i = 0; i < 36; i++)
	{
		m_gameObjects.push_back(new Enemy(
			new LoaderParams(xPos, -64, 32, 32, "poop")));
		xPos += 20;
	}

#ifdef WIN32
	TheAudioManager::Instance()->PlayBGM();
#endif // WIN32

	return true;
}

bool PlayState::onExit()
{
	std::cout << "exiting PlayState" << std::endl;

	for (int i = 0; i < m_gameObjects.size(); i++)
		m_gameObjects[i]->clean();

	m_gameObjects.clear();

	TheTextureManager::Instance()->clearFromTextureMap("player");
	TheTextureManager::Instance()->clearFromTextureMap("poop");
	TheTextureManager::Instance()->clearFromTextureMap("platform");
	TheTextureManager::Instance()->clearFromTextureMap("background");
	TheTextureManager::Instance()->clearFromTextureMap("cloud1");
	TheTextureManager::Instance()->clearFromTextureMap("cloud2");
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
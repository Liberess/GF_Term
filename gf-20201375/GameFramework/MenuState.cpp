#include "MenuState.h"
#include "PlayState.h"
#include "MenuButton.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameStateMachine.h"
#include <iostream>

const std::string MenuState::s_menuID = "MENU";
MenuState* MenuState::s_pInstance = nullptr;

void MenuState::update()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i]->update();
	}
}

void MenuState::render()
{
	for (int i = 0; i < m_gameObjects.size(); ++i)
	{
		m_gameObjects[i] -> draw();
	}
}

bool MenuState::onEnter()
{
	std::cout << "entering MenuState" << std::endl;
	if (!TheTextureManager::Instance()->load("Assets/UI/button.png",
		"PlayButton", TheGame::Instance()->getRenderer())) {
		return false;
	}
	if (!TheTextureManager::Instance()->load("Assets/UI/exit.png",
		"ExitButton", TheGame::Instance()->getRenderer()))
	{
		return false;
	}

	GameObject* button1 = new MenuButton(new LoaderParams(100, 100,
	400, 100, "PlayButton"),s_menuToPlay);
	GameObject* button2 = new MenuButton(new LoaderParams(100, 300,
	400, 100, "ExitButton"), s_exitFromMenu);

	m_gameObjects.push_back(button1);
	m_gameObjects.push_back(button2);

	return true;
}

bool MenuState::onExit()
{
	std::cout << "exiting MenuState" << std::endl;
	return true;
}

void MenuState::s_menuToPlay()
{
	std::cout << "Play Button Clicked" << std::endl;
	TheGame::Instance()->getStateMachine()->changeState(PlayState::Instance());
}

void MenuState::s_exitFromMenu()
{
	std::cout << "Exit Button Clicked" << std::endl;
	TheGame::Instance()->quit();
}
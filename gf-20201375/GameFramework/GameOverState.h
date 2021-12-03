#pragma once

#include "GameState.h"
#include "MenuState.h"
#include "MenuButton.h"
#include "PlayState.h"
#include "Game.h"
#include "AnimatedGraphic.h"
#include "GameStateMachine.h"
#include "GameObject.h"

class GameOverState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const {return s_gameOverID;}
	static GameOverState* Instance() {
		if (s_pInstance == nullptr)
		{
			s_pInstance = new GameOverState();
		}
		return s_pInstance;
	}

private:
	GameOverState() {}

	static GameOverState* s_pInstance;
	static void s_gameOverToMain();
	static void s_restartPlay();
	static const std::string s_gameOverID;
};
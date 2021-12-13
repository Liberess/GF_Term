#pragma once
#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
	void changeState(GameState* pState);
	void popState();
	void update();
	void render();

private:
	GameState* m_prevState;
	GameState* m_currentState;
};
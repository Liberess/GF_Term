#pragma once
#include "GameState.h"
#include "SDLGameObject.h"

class PlayState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const {return s_playID;}

	static PlayState* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new PlayState();
		
		return s_pInstance;
	}

	bool checkCollision(SDLGameObject* p1, SDLGameObject* p2);

private:
	PlayState(){}

	static PlayState* s_pInstance;
	static const std::string s_playID;
};
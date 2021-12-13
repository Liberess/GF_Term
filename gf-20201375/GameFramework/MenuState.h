#pragma once
#include "GameState.h"

class MenuState : public GameState
{
public:
	virtual void update();
	virtual void render();
	virtual bool onEnter();
	virtual bool onExit();
	virtual std::string getStateID() const {return s_menuID;}
	static MenuState* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new MenuState();
		
		return s_pInstance;
	}

private:
	static MenuState *s_pInstance;
	static const std::string s_menuID;
	MenuState() {}
	static void s_menuToPlay();
	static void s_exitFromMenu();
};
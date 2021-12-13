#pragma once
#include "SDLGameObject.h"
#include "SDL.h"

class Cloud : public SDLGameObject
{
public:
	Cloud(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void init();
	bool checkEndScreen();

private:
	float m_time;
	float m_waitTime;
	float m_moveProbability;
	float m_currentMoveProbability;
	int m_moveSpeed;
	bool m_isMove;
};
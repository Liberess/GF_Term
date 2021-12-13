#pragma once
#include "SDLGameObject.h"
#include <random>

class Enemy : public SDLGameObject
{
public:
	Enemy(const LoaderParams *pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void init();
	bool checkEndGround();

private:
	bool m_isFalling;
	float m_fallProbability;
	float m_waitTime;
	float m_time;
	int m_fallSpeed;
	int m_sfxCount;
};
#pragma once

#include "SDLGameObject.h"
#include "..\Utilities\Timer.h"

class Enemy : public SDLGameObject
{
public:
	Enemy(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	void checkCollision();
	void move();
	virtual void hit();
	virtual void clean();
	virtual void destroy();

private:
	bool m_isHit;
	Timer m_timer;
};
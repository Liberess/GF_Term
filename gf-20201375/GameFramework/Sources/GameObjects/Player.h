#pragma once
#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
	Player(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
	void checkCollision();
	void move();
	void jump();
	void shoot();

private:
	int m_maxJumpHeight;
	float m_shotTime;
	float m_jumpHeight;
	float m_gravity;
};
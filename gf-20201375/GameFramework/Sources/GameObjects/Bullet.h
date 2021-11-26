#pragma once

#include "SDLGameObject.h"

class Bullet : public SDLGameObject
{
public:
	Bullet(const LoaderParams* pParams, const Vector2D& dirc, std::string id);
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void destroy();
	bool IsOutSideScreen();
	void checkCollision();

private:
	std::string m_id;
	Vector2D m_direction;
	bool m_isInteract;
};
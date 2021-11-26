#pragma once

#include "GameObject.h"
#include "SDL.h"
#include "..\Utilities\InputHandler.h"
#include <iostream>
#include <algorithm>
#include <cstdlib>

enum ObjectType
{
	GROUND = 0,
	WALL,
	PLAYER,
	ENEMY,
	BULLET,
	BACKGROUND
};

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(const LoaderParams* pParams);
	virtual ~SDLGameObject() {}
	virtual void draw();
	virtual void update();
	virtual void clean();
	virtual void hit() {}
	virtual void destroy() {}
	int getX() const { return m_position.getX(); }
	int getY() const { return m_position.getY(); }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	bool checkCollision(const SDL_Rect& target, int type = 0);
	SDL_Rect getDestRect() { return m_destRect; }

protected:
	std::string m_textureID;
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	SDL_RendererFlip m_flipX;
	Vector2D m_position;
	Vector2D m_acceleration;
	Vector2D m_velocity;
	int m_moveSpeed;
	int m_jumpSpeed;
	bool m_isJumping;
	bool m_isGround;
	bool m_isObstacle;
	SDL_Rect m_destRect;
};
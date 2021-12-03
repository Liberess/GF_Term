#pragma once

#include <iostream>
#include <SDL.h>
#include "LoaderParams.h"

class GameObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;

protected:
	GameObject(const LoaderParams* pParams)
		: m_currentFrame(0), m_currentRow(0), m_x(0), m_y(0), m_width(0),
		m_height(0), m_flipX(SDL_FLIP_NONE) {}
	virtual ~GameObject() {}

protected:
	int m_x;
	int m_y;
	int m_width;
	int m_height;
	int m_currentRow;
	int m_currentFrame;
	std::string m_textureID;
	SDL_RendererFlip m_flipX;
};
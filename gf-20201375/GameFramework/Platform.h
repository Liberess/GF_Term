#pragma once
#include "SDLGameObject.h"
#include "SDL.h"

class Platform : public SDLGameObject
{
public:
	Platform(const LoaderParams* pParams);
	virtual void draw();
	virtual void update();
	virtual void clean();
};
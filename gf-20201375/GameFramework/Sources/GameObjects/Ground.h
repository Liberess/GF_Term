#ifndef __Ground_H__
#define __Ground_H__

#include "SDLGameObject.h"

class Ground : public SDLGameObject
{
public:
	Ground(const LoaderParams* pParams);
	virtual void draw();
	virtual void update() {}
	virtual void clean() {}
};

#endif
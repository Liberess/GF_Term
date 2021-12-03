#include "Platform.h"

Platform::Platform(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	m_velocity.setX(0.001);
	m_velocity.setY(2);
}

void Platform::draw()
{
	SDLGameObject::draw();
}

void Platform::update()
{
	m_velocity.setX(0);
	m_velocity.setY(0);
}

void Platform::clean()
{

}
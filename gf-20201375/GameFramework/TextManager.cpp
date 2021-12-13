#include "TextManager.h"
#include <iostream>

TextManager* TextManager::s_pInstance = 0;

void TextManager::drawText(const char* str, int x, int y, int size,
	SDL_Color color, SDL_Renderer* pRenderer)
{
	clean();
	TTF_Init();

	TTF_Font* font = TTF_OpenFont("Assets/Jung9.ttf", size);

	m_surface = TTF_RenderText_Solid(font, str, color);
	m_texture = SDL_CreateTextureFromSurface(pRenderer, m_surface);

	int w = 0, h = 0;
	SDL_QueryTexture(m_texture, NULL, NULL, &w, &h);
	SDL_Rect destRect = { x, y, w, h };
	SDL_RenderCopy(pRenderer, m_texture, NULL, &destRect);
}

void TextManager::clean()
{
	SDL_DestroyTexture(m_texture);
	SDL_FreeSurface(m_surface);
	TTF_Quit();
}
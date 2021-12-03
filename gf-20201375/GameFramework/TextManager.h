#pragma once

#include <SDL_ttf.h>
#include <SDL.h>

class TextManager
{
public:
	static TextManager* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new TextManager();
		return s_pInstance;
	}
	~TextManager() {}
	void clean();
	void drawText(const char* str, int x, int y, int size, SDL_Color color, SDL_Renderer* pRenderer);

private:
	TextManager() {}
	static TextManager* s_pInstance;
	SDL_Surface* m_surface;
	SDL_Texture* m_texture;
};

typedef TextManager TheTextManager;
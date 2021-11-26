#pragma once

#include <SDL_ttf.h>
#include <SDL.h>

class TextManager
{
public:
    static TextManager* Instance()
    {
        if (s_pInstance == 0) s_pInstance = new TextManager();
        return s_pInstance;
    }
    ~TextManager() {}
    void init();
    void clean();
    void drawText(const char* str, int x, int y, SDL_Renderer* pRenderer);

private:
    TextManager() {}
    static TextManager* s_pInstance;
    TTF_Font* m_font;
    SDL_Color m_color;
    SDL_Surface* m_surface;
    SDL_Texture* m_texture;
};

typedef TextManager TheTextManager;
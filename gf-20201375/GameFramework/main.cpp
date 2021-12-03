#include <stdio.h>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

SDL_Window* g_pWindow = 0;
SDL_Renderer* g_pRenderer = 0;

SDL_Texture* m_pTexture;
// 원본 사각형
SDL_Rect m_sourceRectangle;
// 대상 사각형
SDL_Rect m_destinationRectangle;

int main(int argc, char* args[])
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0) {

        g_pWindow = SDL_CreateWindow("GF01.HelloSDL",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            640, 480, SDL_WINDOW_SHOWN);

        if (g_pWindow != 0) {
            g_pRenderer = SDL_CreateRenderer(g_pWindow, -1, 0);
        }
    }
    else {
        return 1;
    }

    // SDL Image

    SDL_Surface* pTempSurface = IMG_Load("Assets/animate-alpha.png"); 
    m_pTexture = SDL_CreateTextureFromSurface(g_pRenderer, pTempSurface);
    SDL_FreeSurface(pTempSurface);

    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRectangle.w, &m_sourceRectangle.h);

    m_destinationRectangle.w = m_sourceRectangle.w;
    m_destinationRectangle.h = m_sourceRectangle.h;

    m_destinationRectangle.x = m_sourceRectangle.x = 0;
    m_destinationRectangle.y = m_sourceRectangle.y = 0;



    
    // SDL TTF
    if (TTF_Init() < 0) { printf("오류: 폰트를 초기화할 수 없습니다. (%s)\n", TTF_GetError()); return false; }
    TTF_Font* font = TTF_OpenFont("C:\\Windows\\Fonts\\gulim.ttc", 16); if (font == NULL) { printf("Could not open font! (%s)\n", TTF_GetError()); return -1; }

    SDL_Color color = { 255, 0, 255, SDL_ALPHA_OPAQUE }; 
    SDL_Surface* surface = TTF_RenderText_Blended(font, "Test String", color); 
    SDL_Texture* texture = SDL_CreateTextureFromSurface(g_pRenderer, surface);
    SDL_FreeSurface(surface); 
    SDL_Rect r = { 0, 0, surface->w, surface->h };


    SDL_SetRenderDrawColor(g_pRenderer, 0, 0, 0, 255);
    SDL_RenderClear(g_pRenderer);

    SDL_RenderCopy(g_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
    SDL_RenderCopy(g_pRenderer, texture, NULL, &r);

    SDL_RenderPresent(g_pRenderer);
    SDL_Delay(5000);
    SDL_Quit();
    return 0;
}
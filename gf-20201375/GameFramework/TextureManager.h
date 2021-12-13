#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <map>

class TextureManager
{
public:
	static TextureManager *s_pInstance;
	static TextureManager* Instance()
	{
		if (s_pInstance == nullptr) 
			s_pInstance = new TextureManager();

		return s_pInstance;
	}

public:
	bool load(std::string fileName, std::string id, SDL_Renderer *pRenderer);
	void draw(std::string id, int x, int y, int width, int height,
	SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void drawFrame(std::string id, int x, int y, int width, int height, int currentRow,
	int currentFrame, SDL_Renderer *pRenderer, 
	SDL_RendererFlip flip = SDL_FLIP_NONE);
	void clearFromTextureMap(std::string id)
	{
		m_textureMap.erase(id);
	}

private:
	std::map<std::string, SDL_Texture*> m_textureMap;
	TextureManager() {}
};

typedef TextureManager TheTextureManager;
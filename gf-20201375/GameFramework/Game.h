#pragma once

#include <SDL.h>
#include "TextureManager.h"
#include "GameObject.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"

class GameStateMachine;

class Game
{
public:
	static Game* Instance()
	{
		if (s_pInstance == nullptr)
		{
			s_pInstance = new Game();
			return s_pInstance;
		}
		return s_pInstance;
	}
	SDL_Renderer* getRenderer() const { return m_pRenderer; }
	bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void render();
	void update();
	void handleEvents();
	void clean();
	bool running() { return m_bRunning; }
	void quit();
	GameStateMachine* getStateMachine()
	{
		return m_pGameStateMachine;
	}
	std::vector<GameObject*> m_gameObjects;
private:
	Game() {}
	static Game* s_pInstance;

private:
	int m_currentFrame;

	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;

	bool m_bRunning;

	SDL_Texture* m_pTexture;
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	GameStateMachine* m_pGameStateMachine;
};

typedef Game TheGame;
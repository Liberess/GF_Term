#pragma once

#include <SDL.h>
#include "TextureManager.h"
#include "GameObject.h"
#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Platform.h"

class GameStateMachine;

class Game
{
public:
	static Game* Instance()
	{
		if (s_pInstance == nullptr)
			s_pInstance = new Game();

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
	int getScreenWidth() const { return m_screenWidth; }
	int getScreenHeight() const { return m_screenHeight; }
	std::vector<GameObject*> m_gameObjects;

private:
	Game() : m_currentFrame(0), m_pWindow(nullptr), m_pRenderer(nullptr),
		m_bRunning(false), m_pTexture(nullptr), m_srcRect(), m_destRect(),
		m_pGameStateMachine(nullptr), m_screenWidth(0), m_screenHeight(0) {}
	static Game* s_pInstance;

private:
	int m_currentFrame;
	SDL_Window* m_pWindow;
	SDL_Renderer* m_pRenderer;
	bool m_bRunning;
	SDL_Texture* m_pTexture;
	SDL_Rect m_srcRect;
	SDL_Rect m_destRect;
	GameStateMachine* m_pGameStateMachine;
	int m_screenWidth, m_screenHeight;
};

typedef Game TheGame;
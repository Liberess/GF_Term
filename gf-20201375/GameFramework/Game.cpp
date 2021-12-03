#include "Game.h"
#include "InputHandler.h"
#include "SDL_image.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"

Game* Game::s_pInstance = nullptr;

bool Game::init(const char* title, int xpos, int ypos, int width,
	int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);
		
		if (m_pWindow != 0)
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	}
	else
	{
		return false;		// sdl could not initialize
	}

	if (!TheTextureManager::Instance()->load("Assets/Player/KinoStanding.png",
		"PlayerStanding", m_pRenderer))
	{
		return false;
	}

	// 게임 유한상태기계
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(MenuState::Instance());

	m_bRunning = true;
	return true;
}

void Game::update()
{
	// 상태 단위로 게임 루프 처리
	m_pGameStateMachine->update();
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	m_pGameStateMachine->render();
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	TheInputHandler::Instance()->clean();
	SDL_Quit();
}

void Game::handleEvents()
{
	TheInputHandler::Instance()->update();
}

void Game::quit()
{
	m_bRunning = false;
}
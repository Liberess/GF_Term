#include "Game.h"
#include "InputHandler.h"
#include "SDL_image.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "AudioManager.h"

Game* Game::s_pInstance = nullptr;

bool Game::init(const char* title, int xpos, int ypos, int width,
	int height, bool fullscreen)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, fullscreen);
		
		if (m_pWindow != 0)
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

		// Set Game Screen Size
		m_screenWidth = width;
		m_screenHeight = height;

		SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);
	}
	else
	{
		return false;	
	}

	// Game FSM
	m_pGameStateMachine = new GameStateMachine();
	m_pGameStateMachine->changeState(MenuState::Instance());

#ifdef WIN32
	// Init AudioManager
	TheAudioManager::Instance()->init();
#endif

	m_bRunning = true;
	return true;
}

void Game::update()
{
	// Processing Updates by Status.
	m_pGameStateMachine->update();
}

void Game::render()
{
	SDL_RenderClear(m_pRenderer);
	// Processing Renders by Status.
	m_pGameStateMachine->render();
	SDL_RenderPresent(m_pRenderer);
}

void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	TheInputHandler::Instance()->clean();
#ifdef WIN32
	TheAudioManager::Instance()->clean();
#endif // WIN32

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
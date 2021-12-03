#include "Game.h"

int main(int argc, char* argv[])
{
	const int FPS = 60;
	const int DELAY_TIME = 1000.0f / FPS;

	Uint32 frameStart, frameTime;

	if (TheGame::Instance()->init("Avoiding poop",
		100, 100, 640, 480, false))
	{
		while (TheGame::Instance()->running())
		{
			frameStart = SDL_GetTicks();
			TheGame::Instance()->handleEvents();
			TheGame::Instance()->update();
			TheGame::Instance()->render();
			frameTime = SDL_GetTicks() - frameStart;
			if (frameTime < DELAY_TIME)
				SDL_Delay((int)(DELAY_TIME - frameTime));
		}
	}
	else
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	TheGame::Instance()->clean();

	return 0;
}
#pragma once
#include "SDL.h"
#include <vector>
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2,
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if(s_pInstance == nullptr){
			s_pInstance = new InputHandler();
			}
		return s_pInstance;
	}
	bool isKeyDown(SDL_Scancode key);
	void update();
	void clean();
	~InputHandler() {}

	std::vector<bool> m_mouseButtonStates;
	Vector2D* m_mousePosition;

	bool getMouseButtonState(int buttonNumber);
	Vector2D* getMousePosition();
	void onMouseMove(SDL_Event event);
	void onMouseButtonDown(SDL_Event event);
	void onMouseButtonUp(SDL_Event event);
	void onKeyDown();
	void onKeyUp();
private:
	InputHandler();
	static InputHandler *s_pInstance;
	const Uint8* m_keystates;
};

typedef InputHandler TheInputHandler;
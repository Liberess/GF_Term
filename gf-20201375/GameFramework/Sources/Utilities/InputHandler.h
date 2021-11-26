#ifndef __InputHandler_H__
#define __InputHandler_H__

#include "SDL.h"
#include "Vector2D.h"
#include <vector>

class InputHandler
{
public:
    enum mouse_buttons
    {
        LEFT = 0,
        MIDDLE,
        RIGHT
    };
    ~InputHandler() {}
    static InputHandler* Instance()
    {
        if (s_pInstance == 0)
            s_pInstance = new InputHandler();

        return s_pInstance;
    }
    bool IsKeyDown(SDL_Scancode key);
    void Update();
    void Clean() {}
    bool GetMouseBtnState(int btnNum);
    Vector2D* GetMousePos() const;

private:
    InputHandler();
    static InputHandler* s_pInstance;
    const Uint8* m_keyStates;
    std::vector<bool> m_mouseBtnStates;
    Vector2D* m_mousePos;
    void OnMouseMove(SDL_Event event);
    void OnMouseBtnDown(SDL_Event event);
    void OnMouseBtnUp(SDL_Event event);
    void OnKeyDown();
    void OnKeyUp();
};

typedef InputHandler TheInputHandler;

#endif
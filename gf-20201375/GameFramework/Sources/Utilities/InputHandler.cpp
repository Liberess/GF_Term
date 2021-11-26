#include "InputHandler.h"
#include "..\Game.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler()
{
    m_mousePos = new Vector2D(0, 0);

    for (int i = 0; i < 3; i++)
        m_mouseBtnStates.push_back(false);
}

void InputHandler::Update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT: TheGame::Instance()->quit(); break;
        case SDL_KEYUP: OnKeyUp(); break;
        case SDL_KEYDOWN: OnKeyDown(); break;
        case SDL_MOUSEMOTION: OnMouseMove(event); break;
        case SDL_MOUSEBUTTONDOWN: OnMouseBtnDown(event); break;
        case SDL_MOUSEBUTTONUP: OnMouseBtnUp(event); break;
        default: break;
        }
    }
}

void InputHandler::OnMouseMove(SDL_Event event)
{
    m_mousePos->setX(event.motion.x);
    m_mousePos->setY(event.motion.y);
}

void InputHandler::OnMouseBtnDown(SDL_Event event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
        m_mouseBtnStates[LEFT] = true;
    if (event.button.button == SDL_BUTTON_LEFT)
        m_mouseBtnStates[MIDDLE] = true;
    if (event.button.button == SDL_BUTTON_LEFT)
        m_mouseBtnStates[RIGHT] = true;
}

void InputHandler::OnMouseBtnUp(SDL_Event event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
        m_mouseBtnStates[LEFT] = false;
    if (event.button.button == SDL_BUTTON_LEFT)
        m_mouseBtnStates[MIDDLE] = false;
    if (event.button.button == SDL_BUTTON_LEFT)
        m_mouseBtnStates[RIGHT] = false;
}

void InputHandler::OnKeyDown()
{
    m_keyStates = SDL_GetKeyboardState(0);
}

void InputHandler::OnKeyUp()
{
    m_keyStates = SDL_GetKeyboardState(0);
}

bool InputHandler::IsKeyDown(SDL_Scancode key)
{
    if (m_keyStates != 0)
    {
        if (m_keyStates[key] == 1)
            return true;
        else
            return false;
    }

    return false;
}

bool InputHandler::GetMouseBtnState(int btnNum)
{
    return m_mouseBtnStates[btnNum];
}

Vector2D* InputHandler::GetMousePos() const
{
    return m_mousePos;
}
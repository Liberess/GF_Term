#include "Game.h"
#include "TextManager.h"
#include "TextureManager.h"
#include "GameObjects/Ground.h"
#include "GameObjects/Ground.h"
#include "GameObjects/Player.h"
#include "GameObjects/Enemy.h"
#include "GameObjects/Background.h"
#include "Utilities/Vector2D.h"

Game* Game::s_pInstance = 0;

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (m_pWindow != 0)
        {
            m_screenWidth = width;
            m_screenHeight = height;

            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

            if (m_pRenderer != 0)
            {
                SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
            }
            else return false;
        }
        else return false;
    }
    else
    {
        return false;
    }

    try
    {
        m_gameObjects.clear();

        parseSprite("Assets/background.png", "background");
        m_gameObjects["background"] = new Background(new LoaderParams(0, 0, 640, 480, "background"));

        parseSprite("Assets/ground1.png", "ground1");
        m_gameObjects["ground1"] = new Ground(new LoaderParams(0, 430, 640, 50, "ground1"));

        parseSprite("Assets/wall.png", "wall");
        m_gameObjects["wall"] = new Ground(new LoaderParams(500, 330, 50, 150, "wall"));

        parseSprite("Assets/Ninja_Frog-export.png", "ninja_frog");
        m_gameObjects["player"] = new Player(new LoaderParams(0, 300, 64, 64, "ninja_frog"));

        parseSprite("Assets/Radish-export.png", "enemy");
        m_gameObjects["enemy"] = new Enemy(new LoaderParams(300, 300, 60, 76, "enemy"));

        parseSprite("Assets/bullet.png", "bullet");

        updateCamera();
    }
    catch (std::string expt)
    {
        std::cout << expt << std::endl;
    }

    m_bulletID = 0;
    m_bulletCount = 0;

    m_bRunning = true;
    return true;
}

void Game::destroyGameObject(std::string key)
{
    auto it = m_gameObjects.find(key);

    if (it != m_gameObjects.end())
    {
        // ���� Bullet Object���, Bullet Count�� ���ҽ�Ų��.
        // �ִ�� ������ �� �ִ� �Ѿ��� ���ѵǾ� �ֱ� �����̴�.
        if (key.find("bullet", 0, 5) != std::string::npos)
            --m_bulletCount;

        delete it->second;
        m_gameObjects.erase(key);
    }
}

void Game::parseSprite(std::string path, std::string id)
{
    if (!TheTextureManager::Instance()->load(path, id, m_pRenderer))
        throw path + "�� ��ȿ���� ���� ����Դϴ�.";
}

void Game::instantiateBullet(const SDL_Rect& rect, const Vector2D& dirc)
{
    if (m_bulletCount > 2)
        return;

    std::string key = "bullet" + std::to_string(m_bulletID);
    m_gameObjects[key] = new Bullet(new LoaderParams(rect.x + (rect.w / 2) - 8, rect.y + (rect.h / 2) - 8, 16, 16, "bullet"), dirc, key);

    ++m_bulletID;
    ++m_bulletCount;
}

// Fixed Update
void Game::update()
{
    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
    {
        if (it->second != 0) //�� ����ó���� �ʿ���! �̰��� ����!
            it->second->update();
    }

    updateCamera();
}

// Render Update
void Game::render()
{
    SDL_RenderClear(m_pRenderer);

    for (auto it = m_gameObjects.begin(); it != m_gameObjects.end(); it++)
    {
        if (it->second != 0)
            it->second->draw();
    }

    TheTextManager::Instance()->drawText("GameFrameWork HW2", 50, 50, m_pRenderer);

    SDL_RenderPresent(m_pRenderer);
}

void Game::updateCamera()
{
    SDL_Rect playerRect = { m_gameObjects["player"]->getX(), m_gameObjects["player"]->getY(), m_gameObjects["player"]->getWidth(), m_gameObjects["player"]->getHeight() };

    m_cameraRect.x = (playerRect.x + playerRect.w / 2) - m_screenWidth / 2;
    m_cameraRect.y = (playerRect.y + playerRect.h / 2) - m_screenHeight / 2;

    if (m_cameraRect.x < 0)
        m_cameraRect.x = 0;

    if (m_cameraRect.y < 0)
        m_cameraRect.y = 0;

    if (m_cameraRect.x > (LEVEL_WIDTH - m_cameraRect.w))
        m_cameraRect.x = LEVEL_WIDTH - m_cameraRect.w;

    if (m_cameraRect.y > (LEVEL_HEIGHT - m_cameraRect.h))
        m_cameraRect.y = LEVEL_HEIGHT - m_cameraRect.h;
}

void Game::clean()
{
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
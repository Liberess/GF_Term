#include "Cloud.h"
#include "Game.h"
#include <random>

Cloud::Cloud(const LoaderParams* pParams) :
	SDLGameObject(pParams), m_time(0), m_waitTime(0),
	m_moveProbability(0), m_currentMoveProbability(0),
	m_moveSpeed(1), m_isMove(false)
{
	init();
}

void Cloud::init()
{
	m_isMove = false;

	m_velocity.setX(0);
	m_velocity.setY(0);

	m_position.setX(TheGame::Instance()->getScreenWidth() + m_width); // �����ʿ��� ���

	std::random_device m_randDevice;
	std::mt19937 gen(m_randDevice());
	std::uniform_real_distribution<float> dis1(0.0f, 100.0f); // ��������, ����?
	std::uniform_real_distribution<float> dis2(0.0f, 100.0f); // ��������, ����?
	std::uniform_real_distribution<float> dis3(5.0f, 30.0f); // �Ǵ� ��ٸ���

	m_moveProbability = dis1(gen);
	m_currentMoveProbability = dis2(gen);
	m_waitTime = dis3(gen);
}

void Cloud::draw()
{
	SDLGameObject::draw();
	m_currentFrame = int(((SDL_GetTicks() / 100) % 3));
}

void Cloud::update()
{
	if (checkEndScreen()) // �� ���̶��, �ٽ� ���������� �ʱ�ȭ
		init();

	// ������ �ð��� �ƴٸ�, �����
	if (m_time >= m_waitTime && !m_isMove)
	{
		init();

		// �̰� �³� ������ ������.
		if (m_currentMoveProbability <= m_moveProbability)
			m_isMove = true;
	}
	else
	{
		m_time += 0.01f;
	}

	if (m_isMove) // ��������
		m_velocity.setX(-m_moveSpeed);

	SDLGameObject::update();
}

bool Cloud::checkEndScreen() // �÷��� ���� �����ߴ°�?
{
	if (m_position.getX() + m_width < 0)
		return true;
	else
		return false;
}

void Cloud::clean()
{
	delete this;
}
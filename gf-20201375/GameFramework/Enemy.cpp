#include "Enemy.h"
#include "Game.h"
#include <cmath>

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
	init();
}

void Enemy::init()
{
	m_isFalling = false;

	m_velocity.setX(0);
	m_velocity.setY(0);
	m_position.setY(-64); // 위로

	std::random_device m_randDevice;
	std::mt19937 gen(m_randDevice());
	std::uniform_real_distribution<float> dis1(0.0f, 100.0f); // 내려갈까, 말까?
	std::uniform_real_distribution<float> dis2(2.0f, 10.0f); // 판단 기다릴게

	m_time = 0.0f;

	m_fallProbability = dis1(gen);
	m_waitTime = dis2(gen);

	if (floor(TheGame::Instance()->m_time / 10.0f) > 10)
		m_fallSpeed = 10;
	else if(floor(TheGame::Instance()->m_time / 10.0f) <= 0)
		m_fallSpeed = 1;
	else
		m_fallSpeed = floor(TheGame::Instance()->m_time / 10.0f);
}

void Enemy::draw()
{
	SDLGameObject::draw();
}

void Enemy::update()
{
	if (checkEndGround()) // 땅 끝이라면, 다시 떨어지도록 초기화
		init();

	// 내려갈 시간이 됐다면, 가즈아
	if (m_time >= m_waitTime && !m_isFalling)
	{
		init();

		// 이게 맞나 싶으면 내려가
		if(m_fallProbability < (TheGame::Instance()->m_time + 10.0f) * 1.2f)
			m_isFalling = true;
	}
	else
	{
		m_time += 0.01f;
	}

	if (m_isFalling) // 아래로
		m_velocity.setY(m_fallSpeed);

	SDLGameObject::update();
}

bool Enemy::checkEndGround() // 플랫폼 끝에 도달했는가?
{
	if (m_position.getY() - 16 > TheGame::Instance()->getScreenHeight())
		return true;
	else
		return false;
}

void Enemy::clean()
{

}
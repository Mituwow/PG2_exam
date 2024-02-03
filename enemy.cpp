#include "enemy.h"
#include "Novice.h"


Enemy::Enemy(float x ,float y)
{
	pos_.x = x;
	pos_.y = y;
	radius_ = 15;
	speed_.x = 2.0f;
	speed_.y = 4.0f;
	isAlive = true;
}

void Enemy::Update(int windowWidth,int windowHeight)
{
	pos_.x -= speed_.x;
	pos_.y -= speed_.y;

	if (pos_.x < 0) {
		Respawn(windowWidth);
	}
	if (pos_.y < radius_ || pos_.y > windowHeight - radius_) {
		speed_.y *= -1;
	}
}

void Enemy::Respawn(int windowWidth)
{
	pos_.x = float(windowWidth + rand() % 100);
	pos_.y = float(rand() % 680 + 20);
}

void Enemy::SetIsAliveFalse()
{
	isAlive = false;
	enemyCount++;
}

void Enemy::Draw()
{
	Novice::DrawEllipse(int(pos_.x), int(pos_.y), radius_, radius_, 0, RED, kFillModeSolid);
}
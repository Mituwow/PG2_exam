#include "bullet.h"
#include "Novice.h"

Bullet::Bullet()
{
	pos_.x = -100.0f;
	pos_.y = -100.0f;
	radius_ = 10;
	speed_.x = 8.0f;
	speed_.y = 0.0f;
	isShot_ = false;
	distance_ = 1000;
	checker_ = false;
}

void Bullet::Update()
{
	pos_.x += speed_.x;
	if (pos_.x > float(1280 + radius_)) {
		isShot_ = false;
		SetPosition(-100.0f,-100.0f);
	}
}

void Bullet::Draw()
{
	Novice::DrawEllipse(int(pos_.x), int(pos_.y), radius_, radius_, 0, 0xAFDFE4FF, kFillModeSolid);
}

void Bullet::SetPosition(float x,float y)
{
	pos_.x = x;
	pos_.y = y;
}

void Bullet::Checker(Transform a, int aRadius, Transform b, int bRadius) {

	distance_ = Distance(a.x, a.y, b.x, b.y);
	if (distance_ < aRadius + bRadius) {
		checker_ = true;
	}
	if (distance_ > aRadius + bRadius) {
		checker_ = false;
	}
}
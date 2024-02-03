#include "player.h"
#include "Novice.h"

Player::Player()
{
	pos_.x = 100.0f;
	pos_.y = 360.0f;
	isAlive_ = true;
	isDamaged = false;
	hp_ = 3;
	radius_ = 30;
	speed.x = 0.0f;
	speed.y = 5.0f;
	color_ = BLUE;
	bullet_[10];
	for (int i = 0; i < 10; i++)
	{
		bullet_[i] = new Bullet();
	}
}

void Player::Update(char* keys, char* preKeys)
{
	//Move
	if (keys[DIK_W]) {
		pos_.y -= speed.y;
	}
	if (keys[DIK_S]) {
		pos_.y += speed.y;
	}
	if (pos_.y < radius_) {
		pos_.y = float(radius_);
	}
	if (pos_.y > 720 - radius_) {
		pos_.y = float(720 - radius_);
	}
	//Shot
	for (int i = 0; i < 10; i++)
	{
		if (keys[DIK_SPACE] && !preKeys[DIK_SPACE] && !bullet_[i]->isShot_) {
			bullet_[i]->SetPosition(pos_.x, pos_.y);
			bullet_[i]->isShot_ = true;
			break;
		}

		if (bullet_[i]->isShot_ == true) {
			bullet_[i]->Update();
		}
	}
}

void Player::Draw()
{
	for (int i = 0; i < 10; i++)
	{
		bullet_[i]->Draw();
	}
	Novice::DrawEllipse(int(pos_.x), int(pos_.y), radius_, radius_, 0, color_, kFillModeSolid);
}

void Player::Checker(Transform a, int aRadius, Transform b, int bRadius) {

	distance_ = Distance(a.x, a.y, b.x, b.y);
	if (distance_ < aRadius + bRadius) {
		checker_ = true;
	}
	if (distance_ > aRadius + bRadius) {
		checker_ = false;
	}
}

void Player::SetIsAlive()
{
	hp_--;
	isDamaged = true;
	if (hp_ <= 0) {
		isAlive_ = false;
	}
}
